const url = 'http://127.0.0.1:8081/hello';

const msgpara = document.querySelector('#message');
const sendbtn = document.querySelector('#sendbtn');
const resetbtn = document.querySelector('#resetbtn');
//创建XMLHTTPREQUEST对象
const xhr = new XMLHttpRequest();

xhr.addEventListener("readystatechange", () => {
    console.log(xhr.readyState);
    if (xhr.readyState !== 4) return;
    console.log("123321sdd");
    if (xhr.status === 200) {
        //成功请求，获取文本
        console.log('suc');
        msgpara.textContent = xhr.responseText;
    } else {
        //失败请求，返回响应代号
        new error(xhr.statusText)
    }
});

sendbtn.addEventListener('click', () => {
    xhr.open("GET", url, true);
    xhr.send();

});

resetbtn.addEventListener('click', () => {
    msgpara.textContent = "空消息";
    alert('resetbtn clicked');
});