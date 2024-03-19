//下拉菜单
let my_jd_hd = document.querySelector('.my_jd_hd');
let my_jd  = document.querySelector('.my_jd');
let my_jd_list = document.querySelector('.my_jd_list');

my_jd_hd.onmouseover = function () {
    my_jd.className = 'press_bgd';
    my_jd_list.style.display = 'block';
}
my_jd_hd.onmouseout = function () {
    my_jd.className = 'my_jd';
    my_jd_list.style.display = 'none';
}

let business_purchase_hd = document.querySelector('.business_purchase_hd');
let business_purchase = document.querySelector('.business_purchase');
let purchase_list = document.querySelector('.purchase_list');

business_purchase_hd.onmouseover = function () {
    business_purchase.className = 'press_bgd';
    purchase_list.style.display = 'block';

}
business_purchase_hd.onmouseout = function () {
    business_purchase.className = 'business_purchase';
    purchase_list.style.display = 'none';
}


let store_service_hd = document.querySelector('.store_service_hd');
let store_service = document.querySelector('.store_service');
let store_service_list = document.querySelector('.store_service_list');

store_service_hd.onmouseover = function () {
    store_service.className = 'press_bgd';
    store_service_list.style.display = 'block';
}
store_service_hd.onmouseout = function () {
    store_service.className = 'store_service';
    store_service_list.style.display = 'none';
}


let website_navigation_hd = document.querySelector('.website_navigation_hd');
let website_navigation = document.querySelector('.website_navigation');
let website_navigation_list = document.querySelector('.website_navigation_list');

website_navigation_hd.onmouseover = function () {
    website_navigation.className = 'press_bgd';
    website_navigation_list.style.display = 'block';

}
website_navigation_hd.onmouseout = function () {
    website_navigation.className = 'website_navigation';
    website_navigation_list.style.display = 'none';
}


//我的购物车下拉菜单
let shopping_car = document.querySelector('.shopping_cart');
let drop_down_menu = document.querySelector('.drop_down_menu');

shopping_car.onmouseover = function () {
    drop_down_menu.style.display = 'block';
}
shopping_car.onmouseout = function () {
    drop_down_menu.style.display = 'none';
}


//放大镜效果
let spec_forward = document.querySelector('.spec-forward');
let spec_backward = document.querySelector('.spec-backward');
let spec_small_img_ul = document.querySelector('.spec_small_img>ul');
let spec_small_img_li = document.querySelectorAll('.spec_small_img>ul>li');
let spec_small_img_list = document.querySelector('.spec_small_img>ul>li');
let list_offsetWidth =  spec_small_img_list.offsetWidth+20;
let i = 0

spec_forward.onclick = function() {
    animate(spec_small_img_ul,0)
    i = 0;
}

spec_backward.onclick = function() {
    i++;
    animate(spec_small_img_ul,-list_offsetWidth * (spec_small_img_li.length - 5))
}
 
//实现点击小图出现大图效果
let big_img = document.querySelector('.jqzoom>img');
let small_img = document.querySelectorAll('.spec_small_img>ul>li>img');

for (let i = 0; i < spec_small_img_li.length; i++) {
    spec_small_img_li[i].onmouseover = function() {
        for (let j = 0; j < small_img.length; j++) {
            spec_small_img_li[j].className = '';
        }   
        this.className = 'spec_red';
        //将小图的图片路径赋给大图
        big_img.src = small_img[i].src;
        // 将大图的图片路径赋给超大图
        zoom_div_img.src = big_img.src;
    }
}



// 点击大图显示放大镜
let jqzoom = document.querySelector('.jqzoom');
let zoom_pup = document.querySelector('.zoom-pup');
let zoom_div = document.querySelector('.zoom-div');
let zoom_div_img = document.querySelector('.zoom-div img');
jqzoom.onmouseover = function() {
    zoom_pup.style.display = 'block';
    zoom_div.style.display = 'block';
}

jqzoom.onmouseout = function() {
    zoom_pup.style.display = 'none';
    zoom_div.style.display = 'none';
}

jqzoom.onmousemove = function(e) {
    //获取鼠标到文档最顶部的距离
    let mouse_pageY = e.pageY;
    //获取鼠标到文档最左侧的距离
    let mouse_pageX = e.pageX;
    //获取大图距离文档顶部的距离
    let jqzoom_offsetTop = jqzoom.offsetTop;
    // 获取大图距离文档左侧的距离
    let jqzoom_offsetLeft = jqzoom.offsetLeft;
    //获取黄色小块的高度的一半
    let zoom_pup_height = zoom_pup.clientHeight / 2;
    // 获取黄色小块宽度的一半
    let zoom_pup_Wdith = zoom_pup.clientWidth / 2;
    // 黄块中间鼠标移动的高度距离等于
    let mouse_top = mouse_pageY - jqzoom_offsetTop - zoom_pup_height; 
    //黄快中间鼠标移动的宽度距离等于
    let mouse_left  = mouse_pageX - jqzoom_offsetLeft - zoom_pup_Wdith;
    // 限制小黄快上下的移动距离
    if (mouse_top <= 0) {
        mouse_top = 0;
    } else if(mouse_top >= jqzoom.clientHeight - zoom_pup.clientHeight) {
        mouse_top = jqzoom.clientHeight - zoom_pup.clientHeight;
    }
    // 显示小黄快左右移动的距离
    if (mouse_left <= 0) {
        mouse_left = 0;
    } else if(mouse_left >= jqzoom.clientWidth - zoom_pup.clientWidth) {
        mouse_left = jqzoom.clientWidth - zoom_pup.clientWidth
    }
    // 小黄块上下移动的距离
    zoom_pup.style.top = mouse_top + 'px'; 
    // 小黄快左右的移动距离
    zoom_pup.style.left = mouse_left + 'px';


    //放大镜效果需要等比例缩放
    // 大图的比例运算，上下移动的
    let bigHeight = mouse_top / (jqzoom.clientHeight - zoom_pup.clientHeight); 
    let bigH = bigHeight  * (zoom_div_img.clientHeight - zoom_div.clientHeight);
    zoom_div_img.style.top = -bigH + 'px';
    //大图的比例运算，左右移动的
    let bigLeft = mouse_left / (jqzoom.clientWidth - zoom_pup.clientWidth);
    let bigL = bigLeft * (zoom_div_img .clientWidth - zoom_div.clientWidth);
    zoom_div_img.style.left = -bigL + 'px';
}


//产品选择
let product_type = document.querySelectorAll('.product_type');
for(let i = 0; i < product_type.length; i++) {
    product_type[i].onclick = function() {
        for(let i = 0; i < product_type.length; i++){
            product_type[i].className = 'product_type';
        }
        this.className = 'product_type border_red';
    }
}


// 地区下拉菜单
let region = document.querySelector('.region');
let ui_area_tab = document.querySelector('.ui-area-tab');

region.onmouseover = function() {
    ui_area_tab.style.display = 'block';
}

region.onmouseout = function() {
    ui_area_tab.style.display = 'none';
}

//地区下拉菜单
let area_title = document.querySelectorAll('.area_title>ul>li');
let ui_area_content_list = document.querySelectorAll('.ui-area-content-list');


for(let i = 0;i < area_title.length;i++) {
    area_title[i].setAttribute('index',i);
    area_title[i].onclick = function() {
        for(let i = 0;i < area_title.length;i++) {
            area_title[i].className = '';
        }
        this.className = 'border_red';
       for(let i = 0; i < ui_area_content_list.length; i++) {
        ui_area_content_list[i].style.display = 'none';
        }
        let index = this.getAttribute('index');
        ui_area_content_list[index].style.display = 'block'; 
    }
    
}

//京东服务下拉菜单
let yb_item_cat = document.querySelectorAll('.yb-item-cat');
let more_item = document.querySelectorAll('.more-item');
for (let i = 0;i < yb_item_cat.length;i++) {
    yb_item_cat[i].onmouseover = function() {
        more_item[i].style.display = 'block'
    }

    yb_item_cat[i].onmouseout = function() {
        more_item[i].style.display = 'none'
    }
}

// 分期下拉菜单
let biaotiao_block = document.querySelectorAll('.biaotiao_block');
let biaotiao_drop_down = document.querySelectorAll('.biaotiao_drop_down');
for(let i = 0; i < biaotiao_block.length; i++) {
    biaotiao_block[i].onmouseover = function() {
        biaotiao_drop_down[i].style.display = 'block';
    }
    biaotiao_block[i].onmouseout = function() {
        biaotiao_drop_down[i].style.display = 'none';
    }
}

// 购物车增加
let btn_reduce = document.querySelector('.btn-reduce');
let btn_add = document.querySelector('.btn-add');
let buy_num = document.querySelector('.buy-num');
//点击加号按钮数字增加
btn_reduce.onclick = function() {
    buy_num.value++;
    if(buy_num.value > 1) {
        btn_add.className = 'btn-add';
    }
}
//点击减号按钮数字减少
btn_add.onclick = function() {
    buy_num.value--;
    if(buy_num.value <= 1) {
        buy_num.value = 1;
        btn_add.className = 'btn-add disabled'
    }
}



// 商品介绍部分tab切换栏
let fittings_list = document.querySelectorAll('.fittings_list>li');
let switchable_wrap = document.querySelectorAll('.switchable-wrap');

for(let i = 0; i < fittings_list.length; i++) {
    fittings_list[i].setAttribute('index',i);
    fittings_list[i].onclick = function() {
        for (let i = 0; i < fittings_list.length; i++) {
            fittings_list[i].className = '';
        }
        this.className = 'tab-main-red';
        
        for(let i = 0; i < switchable_wrap.length; i++) {
            switchable_wrap[i].style.display = 'none';
        }
        let index = this.getAttribute('index');
        switchable_wrap[index].style.display = 'block';
    }
}


// 商品内容部分切换栏
let detail_list = document.querySelectorAll('.detail_list>li');
let items = document.querySelectorAll('.items');

for(let j = 0; j < detail_list.length; j++) {
    detail_list[j].setAttribute('index',j);
    detail_list[j].onclick = function() {
        for(let j = 0; j < detail_list.length; j++) {
            detail_list[j].className = '';
        }
        this.className = 'tab-main-red';
        for(let j = 0; j < items.length; j++) {
                items[j].style.display = 'none';
        }
        let index = this.getAttribute('index');
        items[index].style.display = 'block';
    }
}

/**/

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