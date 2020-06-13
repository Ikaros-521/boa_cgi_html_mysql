<script>
        //页面加载   获取全部信息
        $(function(){
            $.ajax({
                type: "POST",//请求方式
                url: "cgi-bin/base_info.json",//地址，就是json文件的请求路径
                dataType: "json",//数据类型可以为 text xml json  script  jsonp
　　　　　　　　　 success: function(result){//返回的参数就是 action里面所有的有get和set方法的参数
                    addBox(result);
                }
            });
            /*$.get("item.json",function(result){
                //result数据添加到box容器中;
                addBox(result);
            });*/
        });
        function addBox(result){
            //result是一个集合,所以需要先遍历
            $.each(result,function(index,obj){
				$(".base_config").append("<p class="p3">常规设置</p>"+
			"<form enctype="multipart/form-data" action="cgi-bin/base_config.cgi" method="post" class="form-horizontal" role="form">"+
				"<div class="form-group" >"+
					"<label class="col-sm-2 control-label">*设备名称：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="device_name" id="focusedInput" type="text" value="+obj['device_name']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group" >"+
					"<label class="col-sm-2 control-label">经纬度：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="LaL" id="focusedInput" type="text" value="+obj['LaL']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group" >"+
					"<label class="col-sm-2 control-label">*灯杆ID：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="lamp_id" id="focusedInput" type="text" value="+obj['lamp_id']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group">"+
					"<label class="col-sm-2 control-label">维护人信息：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="maintainer_info" id="focusedInput" type="text" value="+obj['maintainer_info']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group" >"+
					"<label class="col-sm-2 control-label">*设备IP：</label>"+
					"<div class="col-sm-10">"+
						"<input class="form-control" name="device_ip" id="focusedInput" type="text" value="+obj['device_ip']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group">"+
					"<label class="col-sm-2 control-label">联系方式：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="phone" id="focusedInput" type="text" value="+obj['phone']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group" >"+
					"<label class="col-sm-2 control-label">用户名：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="username" id="focusedInput" type="text" value="+obj['username']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group">"+
					"<label class="col-sm-2 control-label">密码：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="password" id="focusedInput" type="text" value="+obj['password']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group" >"+
					"<label class="col-sm-2 control-label">*网关：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="gateway" id="focusedInput" type="text" value="+obj['gateway']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group">"+
					"<label class="col-sm-2 control-label">*服务器IP：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="server_ip" id="focusedInput" type="text" value="+obj['server_ip']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group" >"+
					"<label class="col-sm-2 control-label">*DNS：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="dns" id="focusedInput" type="text" value="+obj['dns']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group">"+
					"<label class="col-sm-2 control-label">*子网掩码：</label>"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" name="subnet_mask" id="focusedInput" type="text" value="+obj['subnet_mask']+">"+
					"</div>"+
				"</div>"+
				"<div class="form-group">"+
					"<label class="col-sm-2 control-label">是否开启DHCP：</label>"+
					"<label><input name="dhcp" type="text" value="+obj['dhcp']+" /> </label>"+ 
				"</div>"+
				"<div class="form-group">"+
					"<label class="col-sm-2 control-label">是否自动上报异常：</label>"+				
					"<label><input name="error" type="text" value="+obj['error']+" /> </label>"+ 			
				"</div>"+
				"<div class="form-group">"+
					"<div class="col-sm-10">"+
						"<input  class="form-control" id="focusedInput" type="submit" value="提交">"+
					"</div>"+
				"</div>"+
			"</form>"

            });
    	}
</script>



