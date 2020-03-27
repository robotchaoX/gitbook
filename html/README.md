# HTML


### html概述

#### html简介

HTML是 HyperText Mark-up Language 的首字母简写，意思是超文本标记语言，超文本指的是超链接，标记指的是标签，是一种用来制作网页的语言，这种语言由一个个的标签组成，用这种语言制作的文件保存的是一个文本文件，文件的扩展名为html或者htm，一个html文件就是一个网页，html文件用编辑器打开显示的是文本，可以用文本的方式编辑它，如果用浏览器打开，浏览器会按照标签描述内容将文件渲染成网页，显示的网页可以从一个网页链接跳转到另外一个网页。

HTML特点

- 语法非常简洁、比较松散,以相应的英语单词关键字进行组合
- html标签**不区分大小写**
- 大多数标签是成对出现的, 有开始, 有结束.`<html>` `</html>`
- 不成对出现的称之为短标签`<br/>` `<hr/>`

什么是 HTML？

HTML 是用来描述网页的一种语言。

- HTML 指的是超文本标记语言 (**H**yper **T**ext **M**arkup **L**anguage)
- HTML 不是一种编程语言，而是一种*标记语言* (markup language)
- 标记语言是一套*标记标签* (markup tag)
- HTML 使用*标记标签*来描述网页

HTML 标签

HTML 标记标签通常被称为 HTML 标签 (HTML tag)。

- HTML 标签是由*尖括号*包围的关键词，比如 `<html>`
- HTML 标签通常是*成对出现*的，比如 `<b>` 和 `</b>`
- 标签对中的第一个标签是*开始标签*，第二个标签是*结束标签*
- 开始和结束标签也被称为*开放标签*和*闭合标签*

HTML 文档 = 网页

- HTML 文档*描述网页*
- HTML 文档*包含 HTML 标签*和纯文本
- HTML 文档也被称为*网页*

Web 浏览器的作用是读取 HTML 文档，并以网页的形式显示出它们。浏览器不会显示 HTML 标签，而是使用标签来解释页面的内容。

#### html基本结构

一个html的基本结构如下：

```
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>网页标题</title>
    </head>

    <body>
          网页显示内容
    </body>
</html>
```

第一行是文档声明，第二行“`<html>`”标签和最后一行“`</html>`”定义html文档的整体，“`<html>`”标签中的‘lang=“en”’定义网页的语言为英文，定义成中文是'lang="zh-CN"',不定义也没什么影响，它一般作为分析统计用。 “`<head>`”标签和“`<body>`”标签是它的第一层子元素，“`<head>`”标签里面负责对网页进行一些**设置**以及定义标题，设置包括定义网页的编码格式，外链css样式文件和javascript文件等，设置的内容不会显示在网页上，标题的内容会显示在标题栏，“`<body>`”内编写网页上显示的**内容**。

- `<!doctype html>` 声明文档类型
- `<html>` 与 `</html>` 之间的文本描述网页
- `<head>`与`</head>`之间的文本标签里面负责对网页进行一些**设置**以及定义标题
- `<title>`与`</title>`显示在浏览器窗口的标题栏中“网页名称”
- `<body>` 与 `</body>` 之间的文本是可见的页面内容

#### HTML文档版本

<!DOCTYPE> 声明帮助浏览器正确地显示网页。

目前常用的两种文档版本类型是xhtml 1.0和html5

**xhtml 1.0**

xhtml 1.0 是html5之前的一个常用的版本，目前许多网站仍然使用此版本。
文档示例：

```
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
    <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
    <title> xhtml 1.0 文档类型 </title>
</head>
<body>
	<!-- 这是一段注释  -->
</body>
</html>
```

**html5**

html5是向下兼容的
文档示例：

```
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title> html5文档类型 </title>
</head>
<body>
	<!-- 这是一段注释  -->
</body>
</html>
```

**两种文档的区别**

1. 文档声明和编码声明
2. html5新增了标签元素以及元素属性
