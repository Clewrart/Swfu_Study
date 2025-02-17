function checkPassword() {
    var password = document.getElementById("password").value;
    var confirmPassword = document.getElementById("confirmPassword").value;
    var username = document.getElementById("username").value
    var email = document.getElementById("email").value

    if (password !== confirmPassword) {
        alert("两次密码不一致，请检查");
        return false; //不提交

    } else if (password === "" || username === "" || email === "" || confirmPassword === "") {
        alert("请检查填写是否完整！");
        return false; //不提交
    } else {

        alert("恭喜注册成功！请牢记 用户名: " + username + "  和 密码: " + password + "\n点击确认后将跳转至登录页！");
        //弹窗确认后返回登录页
        window.location.href = "{{url_for('regi')}}";
        return true; //提交


    }

}