

### 针对现在屏幕刷新率的问题解决计划

1. 先解决图形绘制的问题
2. 优化i2c的通信，一次完整流程中不需要多次发start和stop信号
3. 图形显示使用buffer来刷新