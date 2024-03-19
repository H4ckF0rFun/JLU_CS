let left_img = document.querySelector('.left_img');
let right_img = document.querySelector('.right_img');
let saomiao_img = document.querySelector('.saomiao_img');
document.write('<script src="js/animate.js"><script>');

saomiao_img.addEventListener('mouseenter',function () {
    //animate(obj,target,callback)
    animate(left_img,20,function () {
        right_img.style.display = 'block';
        
    });
})

saomiao_img.addEventListener('mouseleave',function () {
    //animate(obj,target,callback)
    right_img.style.display = 'none';
    animate(left_img,85);
})
 

let scan_code = document.querySelector('.scan_code');
let login_box =document.querySelector('.login_box');
let login_tab_left = document.querySelector('.login-tab-l');
let login_tab_right = document.querySelector('.login-tab-r');
let font_color1 = document.querySelector('.font_color1');
let font_color2 = document.querySelector('.font_color2');

login_tab_left.addEventListener('click',function() {
    scan_code.style.display = 'block';
    login_box.style.display = 'none';
    font_color1.className = 'font_color1 red_style';
    font_color2.className = 'font_color2';

})

login_tab_right.addEventListener('click',function() {
    scan_code.style.display = 'none';
    login_box.style.display = 'block';
    font_color1.className = 'font_color1 ';
    font_color2.className = 'font_color2 red_style';
})


