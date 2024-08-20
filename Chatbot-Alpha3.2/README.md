## ChatBot机器人使用介绍
- 需要安装`flask`,`dwspark`,`sparkai`等库
    ```bash
    pip install flask,loguru,dwspark,sparkai
    ```
- 使用前需要在`./config.py`中进行配置,如`APPID`,`APIKey`,和`APISecret`以及初始化需要的提示词`prompt`和欢迎语句'Welcome'

- 运行app.py后浏览器进入`127.0.0.1:5000`即可进行聊天

## 待完成
- 图片自动重复解析
- 上传图标bug未修复

## 更新日志:
- Alpha1.0:
    初步完成前后端框架,已经可以进行最基本的对话,不过上下文之间不连贯

- Alpha2.0:
    引入JavaScript,界面更加整洁美观

- Alpha2.1:
    增加欢迎语句,以及将前后文串联,保证对话的流畅度

- Alpha2.2:
    增加初始化训练的模块,可以在初始化时对模型进行训练

- Alpha3.0:
    增加上传图片的功能,同时修复了一些bug

- Alpha3.1:
    使得上传的图片能够显示,美化了界面

- Alpha3.2:
    修复了一些已知bug

> 本项目作者:MayGe