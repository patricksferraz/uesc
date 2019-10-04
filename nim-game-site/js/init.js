(function($){
  $(function(){

    $('.button-collapse').sideNav();
    $('.parallax').parallax();
	$('.scrollspy').scrollSpy();
	$('.modal').modal();
    $('.nav-wrapper>ul.hide-on-med-and-down>li>a')
    	.mouseover(function(event) {
	    	$( this ).css('border-bottom', '2px solid #009688');
	    })
	    .mouseout(function(event) {
	    	$( this ).css('border-bottom', 'none');
	    });
	$("#multijogador").change(function(event)
	{
		if ($("#multijogador").prop("checked"))
			$(".oculto").show();
		else
			$(".oculto").hide();
	});

  }); // end of document ready
})(jQuery); // end of jQuery name space