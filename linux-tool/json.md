## json

------

[TOC]

<!-- toc -->

------

[RapidJSON](http://rapidjson.org/)

JSON: JavaScript Object Notation(JavaScript 对象表示法)

JSON 是存储和交换文本信息的语法。类似 XML。

JSON 比 XML 更小、更快，更易解析。

### JSON 文件

- JSON 文件的文件类型是 ".json"
- JSON 文本的 MIME 类型是 "application/json"

### JSON 语法规则

JSON 语法是 JavaScript 对象表示法语法的子集。

- 数据在名称/值对中
- 数据由逗号分隔
- 花括号保存对象
- 方括号保存数组

### JSON 名称/值对

JSON 数据的书写格式是：名称/值对。

名称/值对包括字段名称（在双引号中），后面写一个冒号，然后是值：`"firstName" : "John"`

### JSON 值

JSON 值可以是：

- 数字（整数或浮点数）
- 字符串（在双引号“ ”中）
- 逻辑值（true 或 false）
- 数组（在方括号[ ]中）
- 对象（在花括号{ }中）无序
- null

### JSON 数字

JSON 数字可以是整型或者浮点型：

```
{ "age":30 }
```

### JSON 字符串

JSON 字符串在双引号中：

```
{ "name":"菜鸟教程" , "url":"www.runoob.com" }
```

### JSON 布尔值

JSON 布尔值可以是 true 或者 false：

```
{ "flag":true }
```

### JSON null

JSON 可以设置 null 值：

```
{ "runoob":null }
```

### JSON 对象

JSON 对象在花括号{ }中书写。
对象可以包含多个**key/value（键/值）**。
对key 必须是字符串，value 可以是合法的 JSON 数据类型（字符串, 数字, 对象, 数组, 布尔值或 null）。
key 和 value 中使用冒号(:)分割。
每个 key/value 对使用逗号(,)分割。

```
{ "name":"runoob", 
  "alexa":10000, 
  "site":null  }
```

### JSON 数组

JSON 数组在方括号中书写。
JSON 中数组值必须是合法的 JSON 数据类型（字符串, 数字, 对象, 数组, 布尔值或 null）。
数组可包含多个对象。

```
{
"name":"网站",
"num":3,
"sites":[ "Google", "Runoob", "Taobao" ],
"age":[30, 10.5, 40],
"employees": [
				{ "firstName":"John" , "lastName":"Doe" },
				{ "firstName":"Anna" , "lastName":"Smith" },
				{ "firstName":"Peter" , "lastName":"Jones" }
			  ]
}
```



