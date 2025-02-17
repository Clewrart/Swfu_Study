let page = 1;
let pageSize = 10;
let totalPage = 0;
let filterConditions = {
    parknum: 'all',
    status: 'all'
};

const statusMap = {
    '0': '空闲',
    '1': '占用',
    '2': '预约',
    '3': '警报'
};

const statusStyleMap = {
    '0': 'text-success',
    '1': 'text-primary',
    '2': 'text-warning',
    '3': 'text-danger'
};


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

function getLocationInfo(currentPage, pageSize) {
    $('#location_list').html('<tr><td colspan="7" class="text-center">加载中......</td></tr>');

    $.ajax({
        url: '/get_location_list',
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
            let locationInfo = data.location_info;
            let total = data.total;
            totalPage = Math.ceil(total / pageSize);

            let tableHtml = '';

            if (locationInfo.length === 0) {
                tableHtml = '<tr><td colspan="7" class="text-center">暂无数据</td></tr>';
            }
            else {
                locationInfo.forEach(item => {
                    const statusText = statusMap[item.status] || '未知';
                    const statusStyle = statusStyleMap[item.status] || '';

                    tableHtml += `
                    <tr>
                        <td>${item.id}</td>
                        <td>${item.parknum}</td>
                        <td>${item.numinpark}</td>
                        <td class="${statusStyle}">${statusText}</td>
                        <td>${item.carnum || '无'}</td>
                        <td>${item.warn_time || '无'}</td>
                        <td>
                            <a href="#" class="delete-location" data-location="${item.id}">删除</a>
                        </td>
                    </tr>`;
                });
            }
            $('#location_list').html(tableHtml);

            if (totalPage <= 1) {
                totalPage = 1;
            }
            $('.pagination').html(generatePagination(currentPage, totalPage));
            $('#listnum').html(`共 ${total} 条记录，当前第 ${currentPage}/${totalPage} 页`);
        },
        error: function (error) {
            console.error('获取数据失败:', error);
            $('#location_list').html('<tr><td colspan="7" class="text-center">获取数据失败</td></tr>');
        }
    });
}

$('#park_id').change(function () {
    filterConditions.parknum = $(this).val();
    page = 1;
    getLocationInfo(page, pageSize);
});

$('.searchbox select:eq(1)').change(function () {
    let status = $(this).val();
    filterConditions.status = status === '全部' ? 'all' : status;
    page = 1;
    getLocationInfo(page, pageSize);
});

function changePage(newPage) {
    if (newPage < 1 || newPage > totalPage || newPage === page) {
        return;
    }
    page = newPage;
    getLocationInfo(page, pageSize);
}

$('.page .pageop').change(function () {
    pageSize = parseInt($(this).val());
    page = 1;
    getLocationInfo(page, pageSize);
});

$('.page-jump input').keypress(function (e) {
    if (e.which === 13) {
        let targetPage = parseInt($(this).val());
        if (targetPage >= 1 && targetPage <= totalPage) {
            page = targetPage;
            getLocationInfo(page, pageSize);
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

function insert_location_info() {
    const parknum = $('#parknum').val();
    const numinpark = $('#location_id').val();
    const longitude = $('#longitude').val();
    const latitude = $('#latitude').val();

    if (!parknum || !numinpark || !longitude || !latitude) {
        showMessage('请填写完整信息');
        return;
    }

    $.ajax({
        url: '/insert_location',
        type: 'POST',
        dataType: 'json',
        contentType: 'application/json',
        data: JSON.stringify({
            'parknum': parknum,
            'numinpark': numinpark,
            'longitude': longitude,
            'latitude': latitude,
        }),
        success: function (response) {
            if (response.status === 'success') {
                $('#myModal').modal('hide');
                $('#myModal2').modal('hide');
                $('#myModal3').modal('hide');
                getLocationInfo(page, pageSize);
                showMessage('添加成功');
            } else {
                showMessage('添加失败' + response.message);
            }
        },
        error: function () {
            showMessage('添加失败，请稍后重试');
        }
    });
}


$(document).ready(function () {
    $(document).on('click', '.delete-location', function (e) {
        e.preventDefault();
        const location = $(this).data('location');

        if (confirm(`确定要删除车场号为 ${location} 的记录吗？`)) {
            $.ajax({
                url: '/delete_location',
                type: 'POST',
                dataType: 'json',
                contentType: 'application/json',
                data: JSON.stringify({
                    'location': location
                }),
                success: function (response) {
                    if (response.status === 'success') {
                        getLocationInfo(page, pageSize);
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

    $("#insert_location").on('click', function () {
        insert_location_info();
    });

    loadParkNumbers();
    getLocationInfo(page, pageSize);
});