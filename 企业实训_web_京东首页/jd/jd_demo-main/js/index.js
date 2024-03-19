// 大轮播图
let big_banner_img = document.getElementById('big_banner_img');
let sider_banner_prev = document.querySelector('.sider_banner_prev');
let sider_banner_next = document.querySelector('.sider_banner_next');
let slide_banner = document.querySelector('.slide_banner');
let dot_list = document.querySelectorAll('.dot>ul>li');
let imgArr = ['lunbotu1.jpg','lunbotu2.jpg','lunbotu3.jpg','lunbotu4.jpg','lunbotu5.jpg','lunbotu6.jpg','lunbotu7.jpg','lunbotu8.jpg']
let i = 0;


//封装切换的函数
//must hold the switch_banner lock when you call this function.
function banner() {
    // 清除小圆点选中的样式
    for (let k = 0; k < dot_list.length; k++) {
        dot_list[k].className = '';
    }
    // 设置图片路径
    big_banner_img.opacity = 0;
    big_banner_img.style = "display:none";
    big_banner_img.idx = 0;

    // 设置小圆点样式
    dot_list[i].className = 'check-dot';

    big_banner_img.timer = setInterval(function(){
        // console.log("计时:" + big_banner_img.opacity.toString())

        if(big_banner_img.idx == 1){
            big_banner_img.src = 'images/' + imgArr[i];
        }else if (big_banner_img.idx == 2){
            big_banner_img.style = "display:inline";
        }

        x = 0.04 * big_banner_img.idx;
        big_banner_img.idx  = big_banner_img.idx + 1;
        big_banner_img.opacity = 1 - Math.exp(-x);

        big_banner_img.style = "opacity: " + big_banner_img.opacity.toString() + ";";
        
        if (big_banner_img.idx == 100){
            big_banner_img.opacity = 1;
            big_banner_img.style = "opacity: " + big_banner_img.opacity.toString() + ";";

            clearInterval(big_banner_img.timer)
            big_banner_img.switch_banner_finish = true;
        }
    },10);
}

//封装自动切换函数
function auto_sider_banner() {
    if(big_banner_img.switch_banner_finish){
        big_banner_img.switch_banner_finish = false;
        i++;
        if (i > imgArr.length - 1) {
            i = 0;
        }
        banner();
    }
}

// 使用定时器自动切换
let timer = setInterval(auto_sider_banner,3000);

//鼠标移入停止定时器
slide_banner.onmouseover = function () {
    clearInterval(timer);
}
//鼠标离开开启定时器
slide_banner.onmouseout = function () {
    timer = setInterval(auto_sider_banner,3000);
}

//点击小圆点
//先拿到所有点
for (let j = 0; j < dot_list.length ; j++) {
    //绑定点击事件
    dot_list[j].onclick = function () {
        i = j;
        banner();
    }
}

//


//点击左按钮向前
big_banner_img.switch_banner_finish = true;
sider_banner_prev.addEventListener('click', function () {
    if (big_banner_img.switch_banner_finish) {
        big_banner_img.switch_banner_finish = false;
       i--;
       if (i < 0) {i = imgArr.length - 1;   //从数组后面数就是-1，-2，-3图片倒着显示
       }
       banner();
    }
})

//点击右按钮向后
sider_banner_next.addEventListener('click',function () {
    if (big_banner_img.switch_banner_finish) {
        big_banner_img.switch_banner_finish = false;
        i++;
        if (i > imgArr.length -1) {
            i = 0;
        }
        banner();
    }
})

// 小轮播图
let right_modeule = document.querySelector('.right_modeule');
let mini_lunbotu = document.querySelector('.mini-lunbotu');
let right_module_list = document.querySelectorAll('.right_module>ul>li');
let left_module_prev = document.querySelector('.left_module_prev');
let right_module_next = document.querySelector('.right_module_next');
let small_banner_img1 = document.getElementById('small_banner_img1');
let small_banner_img2 = document.getElementById('small_banner_img2');
let small_banner_img3 = document.getElementById('small_banner_img3');
let small_banner_imgArr1 = ['small_banner_img11.jpg','small_banner_img12.jpg','small_banner_img13.jpg'];
let small_banner_imgArr2 = ['small_banner_img21.jpg','small_banner_img22.jpg','small_banner_img23.jpg'];
let small_banner_imgArr3 = ['small_banner_img31.jpg','small_banner_img32.jpg','small_banner_img33.jpg'];
let p = 0;



//封装切换图片路径的函数
function right_module_banner() {
    //设置图片路径
    small_banner_img1.src = 'images/' + small_banner_imgArr1[p];
    small_banner_img2.src = 'images/' + small_banner_imgArr2[p];
    small_banner_img3.src = 'images/' + small_banner_imgArr3[p];
}

// 封装自动切换函数
function auto_right_module() {
    p++;
    if (p > small_banner_imgArr1.length - 1) {
        p = 0;
    }
    right_module_banner();
}

let timer_right_module = setInterval(auto_right_module,6000);



//点击左按钮
left_module_prev.onclick = function () {
    p--;
    if (p < 0) {
        p = small_banner_imgArr1.length - 1;
    }
    right_module_banner();
}



//点击右按钮
right_module_next.onclick = function () {
    p++;
    if (p > small_banner_imgArr1.length - 1) {
        p = 0;
    }
    right_module_banner();
}

//倒计时
let hour = document.querySelector('.hour');
let minute = document.querySelector('.minute');
let second = document.querySelector('.second');

let inputTime = +new Date('2024-2-27 14:01:00');
setInterval(countDown,1000);
function countDown() {
    let nowTime = +new Date();
    let times = (inputTime - nowTime) / 1000;

    times = times < 0 ? 0 : times;
    
    let h = parseInt(times / 60 / 60 % 24); //时
    hour.innerHTML = h < 10 ? '0' + h.toString() : h.toString();
    let m = parseInt(times / 60 % 60); //分
    minute.innerHTML = m < 10 ? '0' + m.toString() : m.toString();
    let s = parseInt(times % 60);  //秒
    second.innerHTML = s < 10 ? '0' + s.toString() : s.toString();
}


//发现好物鼠标移动右键按钮变红功能
let left_box = document.querySelector('.left_box');
let red_right_click = document.getElementById('red_right_click');

left_box.addEventListener('mouseover',function () {
    red_right_click.className = 'red_click iconfont';
})
left_box.addEventListener('mouseout',function () {
    red_right_click.className = 'iconfont';
})

//发现好物滚动条----------------------------------------------
//获取到roll_amplitude里面的ul
let roll_amplitude = document.querySelector('.roll_amplitude');
let roll_amplitude_ul = roll_amplitude.querySelector('ul');
//再添加一次ul，用于后面循环
roll_amplitude_ul.innerHTML += roll_amplitude_ul.innerHTML;

//获取到ul左边的值
let left = parseInt(getComputedStyle(roll_amplitude_ul).left);
//封装函数
//falg设置节流阀，防止抖动
let falg = true;
function move() {
    if(falg) {
        falg = false;
        //每次向左减10px
        left -= 1;
        //判断：如果ul小于最后那个px值就让ul的left为0，这里因为添加了一个ul，一共2个所以需要除2
        if(left <= -roll_amplitude_ul.clientWidth / 2) {
            left = 0;
        }
        //ul的left值每次减1px
        roll_amplitude_ul.style.left = left + 'px';
    }
    falg = true;
}
//定时器
let move_time = setInterval(move,25);

//当鼠标移动，停止定时器
roll_amplitude.addEventListener('mouseover',function() {
    clearInterval(move_time);
})
//当鼠标离开，开启定时器
roll_amplitude.addEventListener('mouseout',function() {
    move_time = setInterval(move,25);
})
//发现好物滚动条----------------------------------------------


// JOY寻宝----------------------------------
//获取四个按钮
let tab_head = document.querySelector('.tab_head');
let tab_head_lis = tab_head.querySelectorAll('li');
// 获取四个盒子
let new_joy_list = document.querySelector('.new_joy_list');


let item_s = document.querySelectorAll('.item_s');

for (let i = 0; i < tab_head_lis.length; i++) {
    //给li设置索引号
    tab_head_lis[i].setAttribute('index',i);
    //鼠标事件
    tab_head_lis[i].onclick = function() {
        for (let i = 0; i < tab_head_lis.length; i++) {
            tab_head_lis[i].className = '';
        }
        //当选择li时，给每个li添加红色背景属性
        tab_head_lis[i].className = 'select_red';

        for (let i = 0; i < item_s.length; i++) {
            item_s[i].style.display = 'none';
        }
        let index = this.getAttribute('index');
        item_s[index].style.display = 'block';
    }
}



// JOY寻宝----------------------------------


// 楼层效果
let mod_container = document.querySelector('.mod_container');
let elevator = document.querySelector('.elevator');

let floor = document.querySelectorAll('#app .floor');   //获取到所有楼层
let elevatorA = document.querySelectorAll('.elevator a'); //获取到所有的li

let elevatorArr = [];   //数组中放4个数，分别是每个楼层最底下的数

//封装函数，每次将li的字体颜色清除
function clearColor() {
    for(let i = 0; i<elevatorA.length;i++) {
        elevatorA[i].style.color = '';
    }
}

//基础的高度
let base = mod_container.offsetHeight;

for(let i = 0; i < floor.length; i++) {
    base = base + floor[i].offsetHeight;    //每次基础高度加楼层高度
    elevatorArr.push(base);  //将输入放入数组，但是数组每次的值都会被改变，所以不能直接用
}


let search = document.querySelector('.search');
let form = document.querySelector('.form');
let shopping_cart = document.querySelector('.shopping_cart');
let search_m = document.querySelector('.search-m');
let m_logo = document.querySelector('.m_logo');

// 监听滚动条事件
document.onscroll = function() {
    //获取到滚动条垂直方向滚动了多少
    let top = document.documentElement.scrollTop || document.body.scrollTop;

    //获取到mod_container的高度
    let mod_container_Height = mod_container.offsetHeight; //包括height、padding、border的高度
    
    if(top >= mod_container_Height) {
        elevator.className = 'elevator elevator-fix';
        search.className = 'search search-fix';
        search_m.className = 'search-m search_re';
        form.style.top = '6px';
        shopping_cart.style.top = '6px';
        m_logo.style.display = 'block';
        form.className = 'form animation';


       
    } else {
        elevator.className = 'elevator';
        search.className = 'search';
        search_m.className = 'search-m';
        form.style.top = '25px';
        shopping_cart.style.top = '25px';
        m_logo.style.display = 'none';
        form.className = 'form';  
    }

    if(top < mod_container.offsetHeight) {
        clearColor();
    } else if(top >= mod_container.offsetHeight && top < elevatorArr[0]) {
        clearColor();
        elevatorA[0].style.color = 'red';
    } else if (top >= elevatorArr[0] && top < elevatorArr[1]) {
        clearColor();
        elevatorA[1].style.color = 'red';
    } else if (top >= elevatorArr[1] && top < elevatorArr[2]) {
        clearColor();
        elevatorA[2].style.color = 'red';
    } else if (top >= elevatorArr[2]) {
        clearColor();
        elevatorA[3].style.color = 'red';
    }
}

/* 搜索内容 */
let search_input = document.getElementById("search_input")
let shelper = document.getElementById("shelper")

function OnLoseFocus() {
    shelper.style="display:none";
    shelper.is_focus = false;
}

function GetDefaultProducts(){
    var defaultProducts = ["AAAA", "BBBB", "CCCC","DDDD","EEEE","FFFF"]; 
    return defaultProducts;
}

function SearchProduct(key){
    var allProducts = ["华为手机","苹果手机","小米手机","小米汽车","华为pad","华为笔记本","鸿蒙系统"];
    var matched_list = [];

    for(i = 0;i < allProducts.length;i++){
        if(allProducts[i].indexOf(key)>=0){
            matched_list.push(allProducts[i]);
        }
    }
    return matched_list;
}

function UpdateShelperList(){
    product_list = null;
    if(search_input.value.length == 0){
        product_list = GetDefaultProducts();
    }else{
        product_list = SearchProduct(search_input.value);
    }

    shelper.innerHTML = ""

    for(i = 0; i < product_list.length;i++){
        new_item = "<li><div class=\"search-item\">" + product_list[i] + "</div><div class=\"search-count\"></div></li>"
        shelper.innerHTML += new_item;
    }
}

function OnGetFocus() {
    shelper.style="display:block";
    shelper.is_focus = true;
    UpdateShelperList();
}

function OnChange(){
    if(!shelper.is_focus){
        return;
    }

    UpdateShelperList();
}
/*
    获取焦点后:
        如果内容改变:
            不为空: 则改变显示列表内容
            为空:   显示推荐内容

        如果内容为空,那么就显示推荐

        如果内容不为空,就显示搜索的内容
*/

search_input.addEventListener("focus", OnGetFocus);
search_input.addEventListener("blur",OnLoseFocus)
search_input.addEventListener("input",OnChange)