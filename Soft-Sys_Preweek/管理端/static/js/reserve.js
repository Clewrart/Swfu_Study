let page = 1;
let pageSize = 10;
let totalPage = 0;
let filterConditions = {
    parknum: 'all',
    status: 'all'
};

const statusMap = {
    '0': '无效',
    '1': '有效',
};

const statusStyleMap = {
    '0': 'text-danger',
    '1': 'text-success',
};


function generatePagination(currentPage, totalPages) {
    if (totalPage <= 1) {
        $('.pagination').parent().hide();
        return;
    }
    else{
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

function getReserveInfo(currentPage, pageSize) {
    $('#reserve_info').html('<tr><td colspan="9" class="text-center">加载中......</td></tr>');

    $.ajax({
        url: '/get_reserve_list',
        type: 'POST',
        dataType: 'json',
        contentType: 'application/json',
        data: JSON.stringify({
            'page': currentPage,
            'pageSize': pageSize,
            'parknum': filterConditions.parknum,
            'status': filterConditions.status
        }),
        success: function (data) {
            let reserveinfo = data.reserve_info;
            let total = data.total;
            totalPage = Math.ceil(total / pageSize);

            let tableHtml = '';
            if (reserveinfo.length === 0) {
                tableHtml = '<tr><td colspan="9" class="text-center">暂无数据</td></tr>';
            }
            else {
                reserveinfo.forEach(item => {
                    const statusText = statusMap[item.reserve_status] || '未知';
                    const statusStyle = statusStyleMap[item.reserve_status] || '';

                    tableHtml += `
                    <tr>
                        <td>${item.reserve_id}</td>
                        <td>${item.carnum}</td>
                        <td>${item.expire_time}</td>
                        <td class="${statusStyle}">${statusText}</td>
                        <td>${item.username}</td>
                        <td>${item.phone}</td>
                        <td>${item.parknum}</td>
                        <td>${item.numinpark}</td>
                        <td>
                            <a href="#" class="delete-reserve" data-reserve_id="${item.reserve_id}">删除</a>
                        </td>
                    </tr>`;
                });
            }
            $('#reserve_info').html(tableHtml);

            if (totalPage <= 1) {
                totalPage = 1;
            }
            $('.pagination').html(generatePagination(currentPage, totalPage));
            $('#listnum').html(`共 ${total} 条记录，当前第 ${currentPage}/${totalPage} 页`);
        },
        error: function (error) {
            console.error('获取数据失败:', error);
            $('#reserve_info').html('<tr><td colspan="7" class="text-center">获取数据失败</td></tr>');
        }
    });
}

$('#park_id').change(function () {
    filterConditions.parknum = $(this).val();
    page = 1;
    getReserveInfo(page, pageSize);
});

$('#status_filter').change(function () {
    let status = $(this).val();
    filterConditions.status = status;
    page = 1;
    getReserveInfo(page, pageSize);
});

function changePage(newPage) {
    if (newPage < 1 || newPage > totalPage || newPage === page) {
        return;
    }
    page = newPage;
    getReserveInfo(page, pageSize);
}

$('.page #pageop').change(function () {
    pageSize = parseInt($(this).val());
    page = 1;
    getReserveInfo(page, pageSize);
});

$('.page-jump input').keypress(function (e) {
    if (e.which === 13) {
        let targetPage = parseInt($(this).val());
        if (targetPage >= 1 && targetPage <= totalPage) {
            page = targetPage;
            getReserveInfo(page, pageSize);
        } else {
            showMessage('请输入有效的页码');
            $(this).val(page);
        }
    }
});

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



$(document).ready(function () {

    loadParkNumbers();
    getReserveInfo(page, pageSize);

    $(document).on('click', '.delete-reserve', function (e) {
        e.preventDefault();
        const reserve = $(this).data('reserve_id');

        if (confirm(`确定要删除预约号为 ${reserve} 的记录吗？`)) {
            $.ajax({
                url: '/delete_reserve',
                type: 'POST',
                dataType: 'json',
                contentType: 'application/json',
                data: JSON.stringify({
                    'reserve': reserve
                }),
                success: function (response) {
                    if (response.status === 'success') {
                        getReserveInfo(page, pageSize);
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
});