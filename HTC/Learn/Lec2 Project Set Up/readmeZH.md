# Lec2 建立工程文件

代码版本：[here](https://github.com/Graphic-researcher/Crosa-Conty-3D/tree/a8896b16e1ae112cb5c7c94298b4e997569188f2/HTC/Project/Crosa-Conty-3D/Crosa-Conty-3D)

课程地址：[here](https://www.youtube.com/watch?v=KG8cAGvn9d4&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=5)

## 核心要点

建立工程文件

将引擎核心构建为dll动态库

构建exe可执行文件

将dll链接到exe

## 项目配置

![image-20211009133552522](https://i.loli.net/2021/10/09/xNGmUPAnSr6fKhV.png)

![image-20211009134214094](https://i.loli.net/2021/10/09/fernlLdvmS6Iaw1.png)

![image-20211009135509608](https://i.loli.net/2021/10/09/BGFRXVJ8gIoPpni.png)

## 构建dll

```c++
//test.h:
namespace CC3D {
	_declspec(dllexport) void Print();
}
//test.cpp:
#include"test.h"
#include<stdio.h>
namespace CC3D {
	void Print() {
		printf("HelloWorld!\n");
	}
}
```

![image-20211009141216743](https://i.loli.net/2021/10/09/TV6ZuiqbLgwOxe7.png)

## exe链接dll

```cpp
//App.cpp in SandBox
#include<iostream>
namespace CC3D {
	_declspec(dllimport) void Print();
}
void main()
{
	CC3D::Print();
	system("pause");
}
```

![image-20211009142558926](https://i.loli.net/2021/10/09/QDF6ENJuZiPVWg5.png)

![image-20211009142425561](https://i.loli.net/2021/10/09/s61ai8oUuz59Y4k.png)

## 小技巧

添加间接链接

为项目增加间接目录（而非直接路径，直接路径在别人电脑上就没用了）

![image-20211008215146437](https://i.loli.net/2021/10/08/DG5dYLAOXTKNfPg.png)

### 静态链接

代码版本：[here](https://github.com/Graphic-researcher/Crosa-Conty-3D/tree/43ef369549fd59bc0643af47de6bc2f7130615dd/HTC/Project/CC3D)

![image-20211008221144977](https://i.loli.net/2021/10/08/xECiXTfuAba6zBp.png)

![image-20211008221212060](https://i.loli.net/2021/10/08/pjyt9cxPh3l5fDb.png)

![image-20211008221323358](https://i.loli.net/2021/10/08/wcXeimHf4Dx8g1E.png)

### 动态链接

代码版本：[here](https://github.com/Graphic-researcher/Crosa-Conty-3D/tree/461d56a91c014d53425d9a779e4652fedf549e8e/HTC/Project/CC3D)

![image-20211008224942093](https://i.loli.net/2021/10/08/hN2GngBi6lYZ4IJ.png)

![image-20211008225026226](https://i.loli.net/2021/10/08/kqx2Cev96uGSEHs.png)

### 编写使用静态库

代码版本：[here](https://github.com/Graphic-researcher/Crosa-Conty-3D/tree/a1179996c82a1ed9a2d206817a9f15f2076d468e/HTC/Project/CC3D)

![image-20211009001811096](https://i.loli.net/2021/10/09/9DcAgrZO5SGfh2V.png)

![image-20211009001944128](https://i.loli.net/2021/10/09/fZIgcFL42VvnwQu.png)

### 项目输出目录

代码版本： [here](https://github.com/Graphic-researcher/Crosa-Conty-3D/tree/d264d0ab682f16c152118fff939360f8b054ed07/HTC/Project/CC3D)

![image-20211009130408707](https://i.loli.net/2021/10/09/lA6G9HOW7PfedUD.png)

![image-20211009130440952](https://i.loli.net/2021/10/09/WBhC8V2IpZcY3Kr.png)