
// 菜单js
$(function(){
	var n=$(".top_nav ul li.cur").index();
	$(".top_nav ul li").mouseenter(
		function(){
			$(this).addClass("cur")
			$(this).siblings().removeClass("cur")
		}
	).mouseleave(
		function(){
			$(".top_nav ul li").eq(n).siblings().removeClass("cur");
			$(".top_nav ul li").eq(n).addClass("cur")
		}
	)
})

// 侧边栏
$(function(){
	$(".side_box").hide()
    window.onscroll=function(){
    var autoheight=document.body.scrollTop||document.documentElement.scrollTop;
    if(autoheight>240){
        $(".side_box").fadeIn(500)
        }else{
            $(".side_box").fadeOut(500)
        }
    }
	$(".sidetop").click(
        function(){
            $('body,html').animate({"scrollTop":0},500);
        }
    )
})

