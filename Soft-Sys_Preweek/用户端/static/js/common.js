window.showMessage = function (message) {
    const messageDiv = $('<div>', {
        class: 'message-toast',
        text: message
    }).css({
        'position': 'fixed',
        'top': '10%',
        'left': '50%',
        'transform': 'translate(-50%, -50%)',
        'background-color': 'rgba(0, 0, 0, 0.7)',
        'color': 'white',
        'padding': '10px 20px',
        'border-radius': '4px',
        'z-index': '9999'
    });

    $('body').append(messageDiv);

    setTimeout(function () {
        messageDiv.fadeOut('fast', function () {
            $(this).remove();
        });
    }, 2000);
}

function getUserName() {
    $.ajax({
        url: "/get_user_name",
        type: "GET",
        dataType: "json",
        contentType: "application/json",
        success: function (data) {
            if (data.status === 'success') {
                $("#welcome").text(`欢迎您 ` + `${data.username}`);
            }
            else {
                showMessage(data.msg);
                window.location.href = "/login";
            }
        },
        error: function (data) {
            showMessage(data.msg);
        }
    });
}

function logout() {
    $.ajax({
        url: "/logout",
        type: "GET",
        dataType: "json",
        contentType: "application/json",
        success: function (data) {
            if (data.status === 'success') {
                showMessage(data.msg);
                window.location.href = "/login";
            }
            else {
                showMessage(data.msg);
            }
        },
        error: function (data) {
            showMessage(data.msg);
        }
    });
}

$(document).ready(function () {
    getUserName();
    document.getElementById("logout").addEventListener("click", logout);
});

