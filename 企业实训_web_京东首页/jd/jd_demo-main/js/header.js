// 关闭头部导航
let head_adv = document.querySelector('.head_advertisement')
let close_nav = head_adv.querySelector('.button span');


close_nav.onclick = function () {
    head_adv.style.display = 'none';
}

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
