document.addEventListener('DOMContentLoaded', function () {
    var elems = document.querySelectorAll('.sidenav');
    var instances = M.Sidenav.init(elems);
});

function request(id) {
    document.getElementById(id).disabled = true;
    var jqxhr = $.ajax('/request/' + id,
        {
            method: 'GET'
        })
        .done(
            function (data) {
                if (data === 'ok') {
                    var video = document.getElementById('video' + id);
                    // video.load();
                    setTimeout(() => {
                        video.src = "http://192.168.1.133:" + (8080 + id) + "/demo.ogg"
                        video.load()
                    }, 5000);
                    video.canplay = alert('请求视频成功');
                } else {
                    console.log('请求视频失败')
                }
            })
        .fail(
            function (xhr, status) {
                console.log('失败: ' + xhr.status + ', 原因: ' + status);
            });
}


function flushNodeList() {
    setInterval(myrefresh, 3000);
}
function myrefresh() {
    var jqxhr = $.ajax('/nodelist',
        {
            method: 'GET',
            dataType: 'json'
        })
        .done(
            function (data) {
                for (i = 0; i < data.length; i++) {
                    var x = data[i]['node'];
                    document.getElementById(x.toString(10)).disabled = false;
                }
            })
        .fail(
            function (xhr, status) {
                console.log('失败: ' + xhr.status + ', 原因: ' + status);
            });
}