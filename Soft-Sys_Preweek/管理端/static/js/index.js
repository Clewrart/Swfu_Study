let page = 1;
let pageSize = 10;
let totalPage = 0;
let currentStatus = 'all';
let currentCarnum = '';

let statusMap = {
    'all': '全部',
    '0': '外出',
    '1': '已停车',
    '2': '已预约',
    '3': '超时'
};

const statusStyleMap = {
    '0': 'text-success',
    '1': 'text-primary',
    '2': 'text-warning',
    '3': 'text-danger'
};

function initPagination() {
    $('.form-control[name="pageSize"]').on('change', function () {
        pageSize = parseInt($(this).val());
        page = 1;
        getCarInfo(page, pageSize);
        updatePagination();
    });

    $('.page-jump input').keypress(function (e) {
        if (e.which === 13) {
            let targetPage = parseInt($(this).val());
            if (targetPage >= 1 && targetPage <= totalPage) {
                page = targetPage;
                getCarInfo(page, pageSize);
            } else {
                showMessage('请输入有效的页码');
                $(this).val(page);
            }
        }
    });

    $(document).on('click', '.pagination li:not(.disabled) a', function (e) {
        e.preventDefault();
        let action = $(this).attr('data-action');

        if (action === 'prev' && page > 1) {
            page--;
        } else if (action === 'next' && page < totalPage) {
            page++;
        } else if (action === 'page') {
            page = parseInt($(this).text());
        }

        getCarInfo(page, pageSize);
        updatePagination();
    });
}


function getCarInfo(currentPage, pageSize) {
    $('#carinfo').html('<tr><td colspan="5" class="text-center">加载中......</td></tr>');

    $.ajax({
        url: '/get_car_list',
        type: 'POST',
        dataType: 'json',
        contentType: 'application/json',
        data: JSON.stringify({
            'page': currentPage,
            'pageSize': pageSize,
            'status': currentStatus,
            'carnum': currentCarnum
        }),
        success: function (data) {
            let carinfo = data.carinfo;
            let total = data.total;
            totalPage = Math.ceil(total / pageSize);

            let html = '';
            if (carinfo.length === 0) {
                html = '<tr><td colspan="5" class="text-center">暂无数据</td></tr>';
            } else {
                carinfo.forEach(car => {
                    const statusText = statusMap[car.status] || '未知';
                    const statusStyle = statusStyleMap[car.status] || '';
                    html += `
                    <tr>
                        <td>${car.carnum}</td>
                        <td class="${statusStyle}">${statusText}</td>
                        <td>${car.ownername}</td>
                        <td>${car.phone}</td>
                        <td>
                            <a href="#" data-toggle="modal" data-target="#myModal" data-carnum="${car.carnum}">编辑</a>
                            <a href="#" class="delete-car" data-carnum="${car.carnum}">删除</a>
                        </td>
                    </tr>
                    `;
                });
            }

            $('#carinfo').html(html);
            $('#listnum').html(`共 ${total} 条记录` + '第 ' + page + ' / ' + totalPage + ' 页');
            updatePagination();
            $('.page-jump input').val(page);
        },
        error: function (xhr) {
            $('#carinfo').html('<tr><td colspan="5" class="text-center">加载失败</td></tr>');
            console.error('Failed to fetch car info:', xhr);
        }
    });
}

$('#status').change(function () {
    currentStatus = $(this).val();
    page = 1;
    getCarInfo(page, pageSize);
});

function updatePagination() {
    if (totalPage <= 1) {
        $('.pagination').parent().hide();
        return;
    }

    $('.pagination').parent().show();
    let html = '';

    html += `
        <li class="${page === 1 ? 'disabled' : ''}">
            <a href="#" data-action="prev" aria-label="Previous">
                <span aria-hidden="true">«</span>
            </a>
        </li>
    `;

    let startPage = Math.max(1, page - 2);
    let endPage = Math.min(totalPage, startPage + 4);

    if (endPage - startPage < 4) {
        startPage = Math.max(1, endPage - 4);
    }

    for (let i = startPage; i <= endPage; i++) {
        html += `
            <li class="${page === i ? 'active' : ''}">
                <a href="#" data-action="page">${i}</a>
            </li>
        `;
    }

    html += `
        <li class="${page === totalPage ? 'disabled' : ''}">
            <a href="#" data-action="next" aria-label="Next">
                <span aria-hidden="true">»</span>
            </a>
        </li>
    `;

    $('.pagination').html(html);
}

const pageSizeSelect = `
    <select class="form-control" name="pageSize">
        <option value="10" ${pageSize === 10 ? 'selected' : ''}>10条每页</option>
        <option value="20" ${pageSize === 20 ? 'selected' : ''}>20条每页</option>
    </select>
`;

let userid = '';
let carid = '';

function get_edit_car_info(carnum) {
    $.ajax({
        url: '/get_eidt_car_info',
        type: 'POST',
        dataType: 'json',
        contentType: 'application/json',
        data: JSON.stringify({
            'carnum': carnum
        }),
        success: function (data) {
            let carinfo = data.car_info;
            userid = carinfo.userid;
            carid = carinfo.carid;
            $('#phone').val(carinfo.phone);
            $('#car_num').val(carinfo.carnum);
            $('#owner_name').val(carinfo.owner);
        },
        error: function (xhr) {
            console.error('Failed to fetch car info:', xhr);
        }
    });
}

function save_car_info() {
    const carnum = $('#car_num').val().trim();
    const phone = $('#phone').val().trim();
    const owner = $('#owner_name').val().trim();

    if (!carnum || !phone || !owner) {
        showMessage('请填写完整信息');
        return;
    }

    $.ajax({
        url: '/save_car_info',
        type: 'POST',
        dataType: 'json',
        contentType: 'application/json',
        data: JSON.stringify({
            'userid': userid,
            'carid': carid,
            'carnum': carnum,
            'phone': phone,
            'owner': owner
        }),
        success: function (response) {
            if (response.status === 'success') {
                $('#myModal').modal('hide');
                getCarInfo(page, pageSize);
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
    $('.pull-left.p-r-20.p-l-20').html(pageSizeSelect);

    $("insert").on('click', function () {
        insert_car_info();
    });

    initPagination();

    $('#myModal').on('shown.bs.modal', function (e) {
        const carnum = $(e.relatedTarget).data('carnum');
        get_edit_car_info(carnum);
    });

    $("#edit_car").on('click', save_car_info);


    $(document).on('click', '.delete-car', function (e) {
        e.preventDefault();
        const carnum = $(this).data('carnum');

        if (confirm(`确定要删除车牌号为 ${carnum} 的记录吗？`)) {
            $.ajax({
                url: '/delete_car',
                type: 'POST',
                dataType: 'json',
                contentType: 'application/json',
                data: JSON.stringify({
                    'carnum': carnum
                }),
                success: function (response) {
                    if (response.status === 'success') {
                        getCarInfo(page, pageSize);
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

    $('#query').on('click', function () {
        currentCarnum = $('#carnum').val().trim();
        page = 1;
        getCarInfo(page, pageSize);
    });

    $('#carnum').on('change keypress', function (e) {
        if (e.type === 'keypress' && e.which !== 13) {
            return;
        }
        currentCarnum = parseInt($(this).val());
        getCarInfo(page, pageSize);
        updatePagination();
    });

    getCarInfo(page, pageSize);
});