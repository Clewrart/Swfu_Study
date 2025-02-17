let page = 1;
let pageSize = 10;
let totalPage = 0;


function generatePagination(currentPage, totalPages) {
    if (totalPage <= 1) {
        $('.pagination').parent().hide();
        return;
    }
    else {
        $('.pagination').parent().show();
    }


    let html = '';

    html += `<li class="${currentPage === 1 ? 'disabled' : ''}">
        <a href="javascript:void(0)" onclick="changePage(${currentPage - 1})" aria-label="Previous">
            <span aria-hidden="true">&laquo;</span>
        </a>
    </li>`;

    let startPage = Math.max(1, currentPage - 2);
    let endPage = Math.min(totalPages, currentPage + 2);

    if (startPage > 1) {
        html += `<li><a href="javascript:void(0)" onclick="changePage(1)">1</a></li>`;
        if (startPage > 2) {
            html += '<li class="disabled"><span>...</span></li>';
        }
    }

    for (let i = startPage; i <= endPage; i++) {
        html += `<li class="${i === currentPage ? 'active' : ''}">
            <a href="javascript:void(0)" onclick="changePage(${i})">${i}</a>
        </li>`;
    }

    if (endPage < totalPages) {
        if (endPage < totalPages - 1) {
            html += '<li class="disabled"><span>...</span></li>';
        }
        html += `<li><a href="javascript:void(0)" onclick="changePage(${totalPages})">${totalPages}</a></li>`;
    }

    html += `<li class="${currentPage === totalPages ? 'disabled' : ''}">
        <a href="javascript:void(0)" onclick="changePage(${currentPage + 1})" aria-label="Next">
            <span aria-hidden="true">&raquo;</span>
        </a>
    </li>`;

    return html;
}

function getUserInfo(currentPage, pageSize) {
    $('#user_list').html('<tr><td colspan="9" class="text-center">加载中......</td></tr>');

    $.ajax({
        url: '/get_user_list',
        type: 'POST',
        dataType: 'json',
        contentType: 'application/json',
        data: JSON.stringify({
            'page': currentPage,
            'pageSize': pageSize,
        }),
        success: function (data) {
            let user_list = data.user_list;
            let total = data.total;
            totalPage = Math.ceil(total / pageSize);

            let tableHtml = '';
            if (user_list.length === 0) {
                tableHtml = '<tr><td colspan="9" class="text-center">暂无数据</td></tr>';
            }
            else {
                user_list.forEach(item => {

                    tableHtml += `
                    <tr>
                        <td>${item.id}</td>
                        <td>${item.username}</td>
                        <td>${item.phonenum}</td>
                        <td>
                            <a href="#" data-toggle="modal" data-target="#myModal" data-user="${item.id}">编辑</a>
                            <a href="#" class="delete-user" data-user="${item.id}">删除</a>
                        </td>
                    </tr>`;
                });

            }
            $('#user_list').html(tableHtml);

            if (totalPage <= 1) {
                totalPage = 1;
            }
            $('.pagination').html(generatePagination(currentPage, totalPage));
            $('#listnum').html(`共 ${total} 条记录，当前第 ${currentPage}/${totalPage} 页`);
        },
        error: function (error) {
            console.error('获取数据失败:', error);
            $('#user_list').html('<tr><td colspan="7" class="text-center">获取数据失败</td></tr>');
        }
    });
}

$('#park_id').change(function () {
    filterConditions.parknum = $(this).val();
    page = 1;
    getUserInfo(page, pageSize);
});

$('#status_filter').change(function () {
    let status = $(this).val();
    filterConditions.status = status;
    page = 1;
    getUserInfo(page, pageSize);
});

function changePage(newPage) {
    if (newPage < 1 || newPage > totalPage || newPage === page) {
        return;
    }
    page = newPage;
    getUserInfo(page, pageSize);
}

$('.page .pageop').change(function () {
    pageSize = parseInt($(this).val());
    page = 1;
    getUserInfo(page, pageSize);
});

$('.page-jump input').keypress(function (e) {
    if (e.which === 13) {
        let targetPage = parseInt($(this).val());
        if (targetPage >= 1 && targetPage <= totalPage) {
            page = targetPage;
            getUserInfo(page, pageSize);
        } else {
            showMessage('请输入有效的页码');
            $(this).val(page);
        }
    }
});

$("")

function loadParkNumbers() {
    $.ajax({
        url: '/get_distinct_parknum',
        type: 'GET',
        success: function (data) {
            if (data.status === "success") {
                let html = '<option value="all">全部</option>';
                data.parknums.forEach(item => {
                    html += `<option value="${item.parknum}">${item.parknum}</option>`;
                });
                $('#park_id').html(html);
            }
        },
        error: function (error) {
            console.error('获取车场号失败:', error);
        }
    });
}

function get_edit_user_info(user) {
    $.ajax({
        url: '/get_edit_user_info',
        type: 'POST',
        dataType: 'json',
        contentType: 'application/json',
        data: JSON.stringify({
            'user': user
        }),
        success: function (response) {
            const user_info = response.user_info;
            if (response.status === 'success') {
                $('#username').val(user_info.username);
                $('#phonenum').val(user_info.phonenum);
            } else {
                showMessage('获取用户信息失败');
            }
        },
        error: function () {
            showMessage('获取用户信息失败，请稍后重试');
        }
    });
}

function save_user_info(user) {
    const username = $('#username').val().trim();
    const phonenum = $('#phonenum').val().trim();

    if (!username || !phonenum) {
        showMessage('请填写完整信息');
        return;
    }

    $.ajax({
        url: '/save_user_info',
        type: 'POST',
        dataType: 'json',
        contentType: 'application/json',
        data: JSON.stringify({
            'user_id': user,
            'username': username,
            'phonenum': phonenum
        }),
        success: function (response) {
            if (response.status === 'success') {
                $('#myModal').modal('hide');
                getUserInfo(page, pageSize);
                showMessage('保存成功');
            } else {
                showMessage('保存失败');
            }
        },
        error: function () {
            showMessage('保存失败，请稍后重试');
        }
    });
}

$(document).ready(function () {

    $(document).on('click', '.delete-user', function (e) {
        e.preventDefault();
        const user = $(this).data('user');

        if (confirm(`确定要删除用户id为 ${user} 的记录吗？`)) {
            $.ajax({
                url: '/delete_user',
                type: 'POST',
                dataType: 'json',
                contentType: 'application/json',
                data: JSON.stringify({
                    'user': user
                }),
                success: function (response) {
                    if (response.status === 'success') {
                        getUserInfo(page, pageSize);
                        showMessage('删除成功');
                    } else {
                        showMessage('删除失败');
                    }
                },
                error: function () {
                    showMessage('删除失败，请稍后重试');
                }
            });
        }
    });

    let user = '';

    $('#myModal').on('shown.bs.modal', function (e) {
        user = $(e.relatedTarget).data('user');
        get_edit_user_info(user);
    });

    $("#save_user").on('click', function () {
        save_user_info(user);
    });

    loadParkNumbers();
    getUserInfo(page, pageSize);
});