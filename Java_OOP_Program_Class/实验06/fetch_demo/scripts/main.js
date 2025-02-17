const url = 'http://127.0.0.1:8081/hello';

const msgpara = document.querySelector("#message");
const sendbtn = document.querySelector("#sendbtn");
const resetbtn = document.querySelector("#resetbtn");

function doGet() {
    fetch(url)
        .then(response => response.text())
        .then(text => msgpara.textContent = text)
        .catch(err => console.log(err))
}

sendbtn.addEventListener('click', () => {
    doGet();
});

resetbtn.addEventListener('click', () => {
    msgpara.textContent = "空消息";
});