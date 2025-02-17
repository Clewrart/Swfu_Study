const url = 'http://127.0.0.1:8081/hello';

const msgpara = document.querySelector("#message");
const sendbtn = document.querySelector("#sendbtn");
const resetbtn = document.querySelector("#resetbtn");

function doGet() {
    axios.get(url)
        .then((response) => {
            //向服务器发送请求成功
            msgpara.textContent = '请求成功:' + response['data'];
        })
        .catch((error) => {
            //向服务器发送请求失败
            msgpara.textContent = '请求失败:' + error['message'];
        })
}



sendbtn.addEventListener('click', () => {
    doGet();
});

resetbtn.addEventListener('click', () => {
    msgpara.textContent = "空消息";
});