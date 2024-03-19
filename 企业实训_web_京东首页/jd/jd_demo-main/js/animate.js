// 1. 让盒子每次移动的距离慢慢变小，速度就会慢慢落下来
	// 2. 核心算法：（目标值-现在的位置）/ 10  作为每次移动的距离 步长
	// 3. 停止的条件是：让当前盒子位置等于目标位置就停止定时器
      function animate(obj,target,callback) {
          // console.log(callback);    callback = function () {}   调用的时候用 callback（）

          //先清除以前的定时器，只保留当前的定时器
          clearInterval(obj.timer);
          //给不同的元素指定了不同的定时器
          obj.timer = setInterval(function () {
              //步长值写到定时器的里面
              // 把我们步长值改为整数 不要出现小数的问题
              // var step = Math.ceil((target - obj.offsetLeft) / 10);   不能这么写，因为要后退
              var step = (target - obj.offsetLeft) / 10;
              step = step > 0 ? Math.ceil(step) : Math.floor(step);

            if (obj.offsetLeft == target) {
                //停止动画 本质时停止定时器
                clearInterval(obj.timer);

                //回调函数写到定时器结束里面
                if (callback) {
                    //调用函数
                    callback();
                }
                //可以这样写
                //callback && callback();
            }
            //把每次加1 这个步长值改为一个慢慢变小的值 步长公式：（目标值-现在的位置）/ 10
            obj.style.left = obj.offsetLeft + step + 'px';  //offsetLeft需要重新赋值才能使用
          },10)
      }