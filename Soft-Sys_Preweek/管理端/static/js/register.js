$(document).ready(function () {
    let usernameValid = false;
    let phoneValid = false;
    let passwordValid = false;

    $('#username').on('blur', function () {
        const username = $(this).val();
        if (username) {
            $.ajax({
                url: '/check_username',
                type: 'POST',
                data: JSON.stringify({ username: username }),
                contentType: 'application/json',
                success: function (response) {
                    if (response.exists) {
                        $('#username-error').text('用户名已存在').show();
                        $('#username-success').hide();
                        usernameValid = false;
                    } else {
                        $('#username-error').hide();
                        $('#username-success').show();
                        usernameValid = true;
                    }
                }
            });
        }
    });

    $('#phone').on('blur', function () {
        const phone = $(this).val();
        if (phone) {
            $.ajax({
                url: '/check_phone',
                type: 'POST',
                data: JSON.stringify({ phone: phone }),
                contentType: 'application/json',
                success: function (response) {
                    if (response.exists) {
                        $('#phone-error').text('手机号已被注册').show();
                        $('#phone-success').hide();
                        phoneValid = false;
                    } else {
                        $('#phone-error').hide();
                        $('#phone-success').show();
                        phoneValid = true;
                    }
                }
            });
        }
    });

    $('#confirm-password').on('input', function () {
        const password = $('#password').val();
        const confirmPassword = $(this).val();

        if (password !== confirmPassword) {
            $('#confirm-password-error').text('两次输入的密码不一致').show();
            passwordValid = false;
        } else {
            $('#confirm-password-error').hide();
            passwordValid = true;
        }
    });

    $('#registrationForm').on('submit', function (e) {
        e.preventDefault();

        if (!usernameValid || !phoneValid || !passwordValid) {
            showMessage('请检查表单填写是否正确');
            return;
        }

        const formData = {
            username: $('#username').val(),
            phone: $('#phone').val(),
            password: $('#password').val()
        };

        $.ajax({
            url: '/register_user',
            type: 'POST',
            data: JSON.stringify(formData),
            contentType: 'application/json',
            success: function (response) {
                if (response.status === 'success') {
                    showMessage('注册成功！');
                    window.location.href = '/login';
                } else {
                    showMessage('注册失败：' + response.message);
                }
            },
            error: function () {
                showMessage('注册失败，请稍后重试');
            }
        });
    });
});