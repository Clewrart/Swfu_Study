// 加载http模块
let http = require('http');

// 定义服务器监听端口号
const port = 8899;
let data = {
    "id":1,
    "name":"Java程序设计",
    "authors":["耿祥义","张跃平"],
    "isbn":"9787302473169",
    "tags":["Java","Web"],
    "price":45.8
};

// 定义HTTP响应函数对象
const requestListener = function (req, res) {
    res.writeHead(200, 
        {'Content-Type':'application/json;charset=UTF-8'}
    );
    res.end(JSON.stringify(data));
}

// 创建HTTP服务器并注册回调函数
const server = http.createServer(requestListener);

// 启动服务器并监听端口
server.listen(port, () => {
    // 在终端打印信息
    console.log(`服务器正在监听端口：${port}`);
});
