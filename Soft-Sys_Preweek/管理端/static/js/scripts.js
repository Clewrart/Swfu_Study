// common scripts

(function () {
   "use strict";


   jQuery('.menu-list > a').click(function () {
      event.preventDefault();
      event.stopPropagation();

      var parent = jQuery(this).parent();
      var sub = parent.find('> ul');

      if (!jQuery('body').hasClass('sidebar-collapsed')) {
         if (sub.is(':visible')) {
            sub.slideUp(300, function () {
               parent.removeClass('nav-active');
               jQuery('.body-content').css({ height: '' });
               adjustMainContentHeight();
            });
         } else {
            visibleSubMenuClose();
            parent.addClass('nav-active');
            sub.slideDown(300, function () {
               adjustMainContentHeight();
            });
         }
      }
      return false;
   });

   function visibleSubMenuClose() {

      jQuery('.menu-list').each(function () {
         var t = jQuery(this);
         if (t.hasClass('nav-active')) {
            t.find('> ul').slideUp(300, function () {
               t.removeClass('nav-active');
            });
         }
      });
   }

   function adjustMainContentHeight() {

      // Adjust main content height
      var docHeight = jQuery(document).height();
      if (docHeight > jQuery('.body-content').height())
         jQuery('.body-content').height(docHeight);
   }

   // add class mouse hover

   jQuery('.side-navigation > li').hover(function () {
      jQuery(this).addClass('nav-hover');
   }, function () {
      jQuery(this).removeClass('nav-hover');
   });


   // Toggle Menu

   jQuery('.toggle-btn').click(function () {

      var body = jQuery('body');
      var bodyposition = body.css('position');

      if (bodyposition != 'relative') {

         if (!body.hasClass('sidebar-collapsed')) {
            body.addClass('sidebar-collapsed');
            jQuery('.side-navigation ul').attr('style', '');

         } else {
            body.removeClass('sidebar-collapsed chat-view');
            jQuery('.side-navigation li.active ul').css({ display: 'block' });

         }
      } else {

         if (body.hasClass('sidebar-open'))
            body.removeClass('sidebar-open');
         else
            body.addClass('sidebar-open');

         adjustMainContentHeight();
      }

      var owl = $("#news-feed").data("owlCarousel");
      owl.reinit();

   });


   searchform_reposition();

   jQuery(window).resize(function () {

      if (jQuery('body').css('position') == 'relative') {

         jQuery('body').removeClass('sidebar-collapsed');

      } else {

         jQuery('body').css({ left: '', marginRight: '' });
      }

      searchform_reposition();

   });

   function searchform_reposition() {
      if (jQuery('.search-content').css('position') == 'relative') {
         jQuery('.search-content').insertBefore('.sidebar-left-info .search-field');
      } else {
         jQuery('.search-content').insertAfter('.right-notification');
      }
   }



   // collapsible panel

   $('.panel .tools .t-collapse').click(function () {
      var el = $(this).parents(".panel").children(".panel-body");
      if ($(this).hasClass("fa-chevron-down")) {
         $(this).removeClass("fa-chevron-down").addClass("fa-chevron-up");
         el.slideUp(200);
      } else {
         $(this).removeClass("fa-chevron-up").addClass("fa-chevron-down");
         el.slideDown(200);
      }
   });


   // close panel 
   $('.panel .tools .t-close').click(function () {
      $(this).parents(".panel").parent().remove();
   });


   // side widget close

   $('.side-w-close').on('click', function (ev) {
      ev.preventDefault();
      $(this).parents('.aside-widget').slideUp();
   });
   $('.info .add-people').on('click', function (ev) {
      ev.preventDefault();
      $(this).parents('.tab-pane').children('.aside-widget').slideDown();

   });


   // refresh panel

   $('.box-refresh').on('click', function (br) {
      br.preventDefault();
      $("<div class='refresh-block'><span class='refresh-loader'><i class='fa fa-spinner fa-spin'></i></span></div>").appendTo($(this).parents('.tools').parents('.panel-heading').parents('.panel'));

      setTimeout(function () {
         $('.refresh-block').remove();
      }, 1000);

   });

   // tool tips



   // popovers

   $('.popovers').popover();

   $('#yu').on('click', function (e) {
      e.preventDefault();
      window.location.href = '/reserve';
   });

   $('#car_manage').on('click', function (e) {
      e.preventDefault();
      window.location.href = '/';
   });

   $('#location_manage').on('click', function (e) {
      e.preventDefault();
      window.location.href = '/location';
   });

   $('#user_manage').on('click', function (e) {
      e.preventDefault();
      window.location.href = '/user';
   });

   $('#data_manage').on('click', function (e) {
      e.preventDefault();
      window.location.href = '/data';
   });


})(jQuery);;


