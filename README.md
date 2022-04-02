# 介绍
这是一个基于OpenGL的游戏引擎

整个引擎是在win11上测试的， win10好像有缩放的问题，在设置动态壁纸的时候可能会遇到和系统DPI有关的问题。win11上测试正常。

## Demo介绍
第一个demo是数字雨 可以设为壁纸

第二个是chrome上的恐龙小游戏 高二的时候用libGDX写的，于是搬到了自己的游戏引擎上来

第三个是DOOM火焰效果看了一篇文章 https://fabiensanglard.net/doom_fire_psx/index.html 渲染出来的视频非常像老游戏

第四个是烟花模拟 代码来自 https://codepen.io/MillerTime/pen/XgpNwb

第五个是流体模拟 代码来自 https://github.com/PavelDoGreat/WebGL-Fluid-Simulation

第六个是用傅里叶级数绘画

第七个是Logo制作器跟随Coding Train的视频写的 https://www.youtube.com/watch?v=i-k04yzfMpw

第八个是个简单的粒子系统

第九个是群聚行为模拟学自Coding Train的视频 https://www.youtube.com/watch?v=4hA7G3gup-4&t

第十个是Times Tables Cardioid 学自Mathologer的视频 https://www.youtube.com/watch?v=qhbuKbxJsk8&t

## 相关演示视频
数字雨: https://www.bilibili.com/video/BV1bZ4y1r7r9?spm_id_from=333.999.0.0

群聚行为模拟: https://www.bilibili.com/video/BV1y34y1b733?spm_id_from=333.999.0.0

用傅里叶级数画画: https://www.bilibili.com/video/BV1HT4y1D7pz?spm_id_from=333.999.0.0

Times Tables Cardioid: https://www.bilibili.com/video/BV1KR4y1V7r4?spm_id_from=333.999.0.0

烟花：https://www.bilibili.com/video/BV1iF411W7BJ?spm_id_from=333.999.0.0

流体模拟：https://www.bilibili.com/video/BV1Qq4y1Y7y2?spm_id_from=444.41.0.0

# 有感
3.8 今天写完了实例化渲染感觉真好。其实我心中也想了一下引擎未来的发展，比如实现粒子系统、演员可以执行action、场景自动化管理资源加载和释放、场景之间切换的特效，还有摄像头的各种变换等等，最重要的是给自己的引擎加个开场动画，我发现我还想了挺多的。引擎目前还有很多不足比如对键盘、和鼠标信息的处理不好还有ShapeRenderer绘图效率过低等等，这些不足都是以后要优化的地方。本人也有点懒，但是大学是真的无聊，还是要找点事做的，总之还是加油吧！

3.9 引擎现在已实现文字和贴图的实例化渲染，接下来要处理的就是各种形状绘制的问题、粒子系统，还有键盘鼠标输入处理的问题。我只能说路漫漫其修远兮，吾将上下而求索。

3.12 今天累死了不想动了赶紧打几把星际

3.15 今天优化了渲染参数，但是发现速度还是不够，经过测试发现瓶颈就在fwrite函数上面，经过测试在1920x1080 60FPS的渲染下平均每帧渲染的时间需要足足8ms每秒渲染114帧，在1000x1000 60FPS下帧平均时间为4ms每秒渲染180FPS，得出瓶颈出在视频编码上，解决这个问题很难。

3.16 今天更新到了ffmpeg的最新版本，渲染时间降低到了2ms，在我的可接受范围内，我知道还可以用libavcodec编码但是我根本就不会，这方面的知识我为0，然后看了一下示例发现是01年的教程，有很多函数都废弃了，于是暂时不想优化视频编码速度了。昨天实现了简单的粒子系统，今天看了一篇文章，我写了个粒子系统实现了火焰特效，把帧数降低到27，在350x350的分辨率下运行，非常有老游戏的感觉。从今天开始学习计算着色器。

3.24 完成了烟花模拟，好像有点bug，但是我不想修了。

3.29 到今天为止，我用我自己写的游戏引擎完成了我以前想做的所有事，感觉非常有成就感。目前已经完善了粒子系统，还优化了ShapeRenderer的绘图效率，但引擎目前还有很多地方待完善。除了之前想到的之外，我还想到了多线程Logger，对键盘和鼠标的处理我想到了事件机制，但是这方面我不会,于是还得继续学习。下一步在完善系统的同时准备复刻超级马里奥，小时候玩过的经典游戏。

3.30 今天发现了一个好奇怪的现象，也是为什么之前引擎改成了只允许贴图等类在堆上创建。在我的恐龙游戏中 jump函数和update函数中打印speed的地址居然是不一样的，非常奇怪。导致了Dinosaur注册了鼠标事件后，左键单击鼠标恐龙却跳不起来。然后在MyScene中把Dinosaur改成Dinosaur*一切都正常了，就更奇怪了。其实之前也遇到过，以前Texture可以在栈上创建，然后也是在恐龙游戏中，地面的贴图会莫名其妙地消失，当我只允许贴图在堆上创建时，地面贴图会正常显示。今天我找到了问题的解决方法，在自定义的Scene中除了int float double等变量外class struct都得在堆上创建。