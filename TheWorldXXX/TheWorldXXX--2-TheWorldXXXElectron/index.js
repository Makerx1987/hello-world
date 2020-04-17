var wins = []
$(function () {
  function change(key) {
    $('.tabs li').removeClass('active');
    $('#tab-' + key).addClass('active');

    $('.contents li').removeClass('active');
    $('#content-' + key).addClass('active');

    if (wins.length <= 0) {
      return;
    } else {
      for (let i = 0; i < wins.length; i++)
        if (wins[i][0] == key) {
          wins[i][1].show();
        } else {
          wins[i][1].hide();
        }
    }
  }

  // 点击菜单
  $('.menu >li').on('click', function (e) {
    var key = parseInt($(this).attr('id').replace('menu-', ''));
    var url = $(this).attr('title')
    console.log(url)

    // 如果没有 tab 则添加 tab
    if (!$('#tab-' + key)[0]) {
      $('.tabs').append('<li id="tab-' + key + '">tab of menu ' + key + ' <i class="close">×</i></li>');
    }

    // 如果没 content 则添加 content
    // if(!$('#content-' + key)[0]) {
    //   // 实际内容动态获取
    //   $('.contents').append('<li id="content-' + key + '">content ' + key + '</li>');
    // }
    if (wins.length <= 0) {
      createsubWindow(key, url);
    } else {
      var ise = false;
      for (let i = 0; i < wins.length; i++)
        if (wins[i][0] == key) {
          ise = true;
          change(key);
          return
        }
      if (!ise) createsubWindow(key, url);
    }

    // 切换到当前点击的 tab 中
    change(key);
  });

  // 点击 tab, 注意使用代理
  $('.tabs').on('click', '>li', function (e) {
    var key = $(this).attr('id').replace('tab-', '');

    // 切换到当前点击的 tab 中
    change(key);
  });

  // 点击关闭按钮
  $('.tabs').on('click', '.close', function (e) {
    // 阻止冒泡事件
    e.stopPropagation();

    // 至少一个活动 tab
    if ($('.tabs li').length <= 1) {
      alert('至少一个活动 tab');
      return;
    }

    var parent = $(this).parents('li');
    var key = parent.attr('id').replace('tab-', '');

    // 删除 tab 和 content
    $('#tab-' + key).remove();
    $('#content-' + key).remove();

    // 如果关闭的 tab 是当前活动 tab 则
    var nccc=parent.attr('class').indexOf('active');
    if (nccc != -1) {
      var newKey = parseInt(parent.attr('id').replace('tab-', ''))
      change(newKey-1);
    }
  });

});

function createsubWindow(key, url) {
  const { BrowserWindow } = require('electron').remote
  // 创建浏览器窗口。
  let win = new BrowserWindow({ width: 1189, height: 640, x: 230, y: 117, resizable: false, movable: false, frame: false })
  wins.push([key, win])
  // 然后加载应用的 index.html。
  if (url == "about.html") win.loadFile("about.html");
  else win.loadURL(url)

  // // 打开开发者工具
  // win.webContents.openDevTools()

  // 当 window 被关闭，这个事件会被触发。
  win.on('closed', () => {
    // 取消引用 window 对象，如果你的应用支持多窗口的话，
    // 通常会把多个 window 对象存放在一个数组里面，
    // 与此同时，你应该删除相应的元素。
    win = null
  })

}