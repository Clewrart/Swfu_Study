function login() {

    var username = document.getElementById("username").value;
    var password = document.getElementById("password").value;
    var data = {
        'username': username,
        'password': password
    };
    $.ajax({
        url: "/login_submit",
        type: "POST",
        dataType: "json",
        contentType: "application/json",
        data: JSON.stringify(data),
        success: function (data) {
            if (data.status === 'success') {
                showMessage(data.msg);
                window.location.href = "/";
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

document.getElementById("login").addEventListener("click", login);