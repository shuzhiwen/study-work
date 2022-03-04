## 目录结构

* _[一、Http 和 Https](#一http-和-https)_
* _[二、React 的生命周期](#二react-的生命周期)_
* _[三、Javascript 的事件循环](#三javascript-的事件循环)_
* _[四、React 技术栈](#四react-技术栈)_
* _[五、跨域的解决方案以及为什么会有跨域问题](#五跨域的解决方案以及为什么会有跨域问题)_
* _[六、Node.js 常用的框架和组件](#六nodejs-常用的框架和组件)_
* _[七、Javascript 是单线程还是多线程](#七javascript-是单线程还是多线程)_
* _[八、React 如何用某种手段保存登录状态](#八react-如何用某种手段保存登录状态)_
* _[九、Javascript 如何进行数组去重](#九javascript-如何进行数组去重)_
* _[十、TCP 和 UDP 的区别](#十tcp-和-udp-的区别)_
* _[十一、React Native 出现的原因](#十一react-native-出现的原因)_
* _[十二、使用过的 React Native 第三方控件库](#十二使用过的-react-native-第三方控件库)_
* _[十三、React 中 class 出现的原因](#十三react-中-class-出现的原因)_
* _[十四、React 中的优化方案](#十四react-中的优化方案)_
* _[十五、在使用 React Native 中遇到了什么困难](#十五在使用-react-native-中遇到了什么困难)_
* _[十六、React-Router 的跳转方式及实现原理](#十六react-router-的跳转方式及实现原理)_
* _[十七、setState 是异步的吗？什么情况下需要用同步的 setState](#十七setstate-是异步的吗什么情况下需要用同步的-setstate)_
* _[十八、如何实现 Javascript 继承机制](#十八如何实现-javascript-继承机制)_
* _[十九、React 在什么情况下会使用 Hook 和高阶组件](#十九react-在什么情况下会使用-hook-和高阶组件)_

## 一、Http 和 Https

#### Http 超文本传输协议（Hyper Text Transfer Protocol）

* Http 是一个基于 TCP/IP 通信协议来传输数据的协议，一般用于 C/S 架构。传输的数据类型为 HTML 文件、图片文件、查询结果等。
* URI：Uniform Resource Identifier 统一资源标识符（是什么）; URL：Uniform Resource Location 统一资源定位符（在哪里）。
* POST 和 GET 的区别: POST 多了请求体 body 用于存放请求数据。GET 请求参数放在 URL 中，而 URL 长度有限制。
* Http 的问题: 信息明文传输容易被截取，数据完整性未校验容易被篡改，没有身份验证机制。

#### Https（Hyper Text Transfer Protocal over Secure Socket Layer）

* Https 通过 SSL 证书来验证服务器的身份，并为浏览器和服务器之间的通信进行加密。
* SSL（Secure Socket Layer）安全套接字层: 位于 TCP/IP 与各种应用层协议之间。
* TLS（Transport Layer Security）传输层安全。
* Https 通信流程: 客户端访问服务器建立 SSL 连接 => 服务端返回证书（包含公钥） => 协商加密等级 => 浏览器生成密钥并用公钥加密 => 将加密后的密钥返回给服务器 => 服务器利用自身私钥解密密钥 => 服务器利用密钥加密与客户端之间的通信。
* Https 的问题: 多次通信导致页面加载时间延长; 缓存没有 Http 高效，增大开销和功耗; 申请 SSL 证书需要资金。

#### http 和 https 的联系

* Https 是 Http 协议的安全版本，Http 协议的数据传输是明文的，是不安全的，Https 使用了 SSL/TLS 协议进行了加密处理。
* 默认端口: Http（80）; Https（443）。

## 二、React 的生命周期

* 挂载: constructor => getDerivedStateFromProps => render => componentDidMount
* 更新: getDerivedStateFromProps => shouldComponentUpdate => render => getSnapshotBeforeUpdate => componentDidUpdate
* 卸载: componentDidUnMount
* 错误: getDerivedStateFromError => componentDidCatch

## 三、Javascript 的事件循环

* Javascript 运行时，除了一个正在运行的主线程，引擎还提供一个（实际按任务类型分为多个）任务队列，里面是需要处理的异步任务。
* 主线程首先会处理同步任务，再将任务队列里满足条件的异步任务纳入主线程，这时异步任务变成了同步任务，如此循环，直到队列为空。
* 异步任务的主要写法是回调函数。异步任务一旦进入主线程就会执行回调函数，没有回调函数的异步任务不会进入任务队列，即不会进入主线程。
* 事件循环: 一种循环检查的机制，只要同步任务执行完了，引擎就会检查挂起的异步任务，是不是可以进入主线程了。
* 维基百科对事件循环的定义: 事件循环是一个程序结构，用于等待和发送消息及事件。

## 四、React 技术栈

* React: 基本开发模块
* React-Router: 前端路由导航
* Redux: 状态（数据）管理
* Babel: 将 ES6 代码转为 ES5 代码
* Webpack: 前端打包工具
* create-react-app 脚手架打包的其他工具

## 五、跨域的解决方案以及为什么会有跨域问题

* 浏览器安全的基石是同源策略，同源指的是协议相同、域名相同、端口相同，目的是保护用户信息安全（表单不受此限制）。
* 非同源受限: Cookie、LocalStorage、IndexDB 等数据不能读取、DOM 无法获得、AJAX 请求不能发送。
* 不同页面在一级域名相同的情况下规避同源策略: 设置 document.domain 为一级域名，二三级域名以下的网页即可进行共享。
* 不同页面在一级域名不同的情况下规避同源策略: 设置 fragment identifier、window.name、window.postMessage 等。

#### AJAX 规避同源策略（重要）: JSONP、WebSocket、CORS

* JSONP（GET）: 简单实用、兼容性好，基本思想是网页通过添加一个 `<script>` 元素，向服务器请求 JSON 数据，注意查询的 callback 参数。
* WebSocket: 一种通信协议，使用 ws://（非加密）和 wss://（加密）作为协议前缀。该协议不实行同源政策，服务器可根据请求的 Origin 字段判断。
* CORS: 跨域资源共享（Cross-Origin Resource Sharing）的缩写，是 W3C 标准，跨域 AJAX 的根本解决方法。

#### CORS 需要浏览器和服务器同时支持，目前主流浏览器都支持此标准（自动处理），实现关键在于服务器。

* 请求分为简单请求和非简单请求; 简单请求是为了兼容表单; 注意简单请求和复杂请求的 Content-Type; 浏览器对这两种请求的处理方式不同。
* 简单请求: 浏览器会在请求头中添加一个 Origin 字段，服务器拒绝则返回正常响应，接收则会在响应中添加以 Access-Control 开头的多个字段。

   * Access-Control-Allow-Origin: 该字段是必须的。它的值要么是请求时 Origin 字段的值，要么是一个 *，表示接受任意域名的请求。
   * Access-Control-Allow-Credentials: 可选字段。它的值是一个布尔值，表示是否允许发送 Cookie。
   * Access-Control-Expose-Headers: 可选字段。指定 getResponseHeader 方法可以拿到的其他字段。
   * 如果要发送 Cookie，Access-Control-Allow-Origin 必须明确指定域名，Cookie 依然遵循同源政策。

* 非简单请求: 在正式请求之前，会增加一次 HTTP 查询请求，称为预检请求，用于验证服务器是否正常工作以及获取某些配置信息。

   * Access-Control-Request-Method: 该字段是必须的。列出浏览器的 CORS 会用到哪些 HTTP 方法（如 PUT）。
   * Access-Control-Request-Headers: 该字段是一个逗号分隔的字符串，指定浏览器 CORS 请求会额外发送的头信息字段。

* 预检请求: 响应字段和简单响应类似，但是字段稍有不同，只有预检通过才可以发送正式请求。

   * Access-Control-Allow-Origin: 含义和简单请求相同。
   * Access-Control-Allow-Methods: 该字段是必须的，它的值是逗号分隔的一个字符串，表明服务器支持的所有跨域请求的方法。
   * Access-Control-Allow-Headers: 如果请求包括 Access-Control-Request-Headers，则响应需要 Access-Control-Allow-Headers。
   * Access-Control-Allow-Credentials: 含义和简单请求相同。
   * Access-Control-Max-Age: 预检请求的有效期，单位为秒，在此期间不用发送另一条预检请求。

## 六、Node.js 常用的框架和组件

* fs: 基础的文件管理模块。
* path: 简化路径操作，提升代码可读性。
* url: 解析 url，拼接 url，生成 url。
* querystring: url 参数字符串与参数对象之间的转换。
* request: 发送 HTTP 请求等。
* express: web 框架（路由等）。
* jsonwebtoken: 处理 token 的有关操作。
* multer: 处理文件类型的 post。
* mysql: 与 mysql 数据库进行通讯。
* xlsx: 处理 excel 表格。

## 七、Javascript 是单线程还是多线程

* Javascript 属于单线程模型，Javascript 只在一个线程上运行不代表 Javascript 引擎只有一个线程。
* 单线程是为了不让浏览器过于复杂，单线程实现比多线程简单，不需要共享资源、信息同步（锁）等，这更适合网页脚本语言。
* 考虑 DOM 操作的场景: 一个线程添加，一个线程删除，线程之间需要协调，势必引出更高的复杂性。单线程更适合与用户交互的场景。
* 单线程的优点是实现简单，执行环境单纯; 缺点是容易造成堵塞，这个问题由事件循环和异步操作解决。

## 八、React 如何用某种手段保存登录状态

* 临时存储: Context, Redux 等。
* 永久存储: LocalStorage 等。

## 九、Javascript 如何进行数组去重

* 暴力检索: 利用 indexOf 等方法进行去重。
* 借助对象: 利用对象属性唯一的特点，每次检索判断数组的值是否为对象中的属性。
* set 集合: 集合是 ES6 的新特性，这是是最简便的方法，只要生成一个 set 实例即可。

## 十、TCP 和 UDP 的区别

* UDP: 面向无连接（不需要三次握手）; 支持单播、多播、广播; 面向报文; 数据传输不可靠（容易丢包）; 传输高效; 适合实时性场景和流媒体传输。
* TCP: 面向连接（需要三次握手）; 仅支持单播; 面向字节流; 数据传输可靠（ACK 等）; 提供拥塞控制; 支持全双工通信; 数据传输效率较低。

## 十一、React Native 出现的原因

* 兼容问题: 一份代码多个平台通用，有利于节省成本，缩短开发周期，减少维护工作。开发效率明显提升。
* 性能问题: H5 应用或者混合应用的运行效率始终比不上原生应用，RN 使用的 UI 组件和原生保持一致，是一个真正的移动应用。
* 调试方便: 原生调试需要重新编译，效率往往比较低，RN 采用 hotReload 的方式大大提高了开发效率（但是运行效率较低）。
* 热更新: 频繁的 APP 升级会让用户感到烦躁，还需要进行多次应用商店审核，热更新化解了这一矛盾，只需从云端下载文件更新即可。

## 十二、使用过的 React Native 第三方控件库

* react-native-elements: 适用于 RN 的 UI 组件库。
* react-native-sound: 处理音频播放。
* react-native-image-crop-picker: 使用相机拍摄图片并裁剪。
* react-native-splash-screen: 配置应用启动画面。
* react-native-vector-icons: 用于自定义图标。
* react-native-modal-datetime-picker: 日期选择组件。
* react-native-navigator: 路由导航。
* react-native-swiper: 轮播图组件。

## 十三、React 中 class 出现的原因

* 使用 class 创建的组件，拥有 state（有状态）和生命周期函数，还可以定义静态类型方法; 运行效率低。
* 使用 function 创建的组件，只有 props，没有生命周期函数，无状态; 运行效率高。
* 使用时应该根据组件有无状态（state）来决定使用哪种类型的组件。

## 十四、React 中的优化方案

* 首次加载时优化: 引入代码分割，组件通过懒加载的方式动态导入。
* 程序运行时优化: 避免不必要的更新和渲染。

   * 使用生产版本而不是开发版本（Create React App 生成的 build 文件就是生产版本）
   * 使用 Chrome 开发者工具检测是否有不相关的组件被错误地更新，从而改进代码。
   * 虚拟化长列表，只更新必要的数据而不会因为过量的 DOM 操作卡顿，使用 react-virtualized。
   * 继承 `React.PureComponent` ，它用当前与之前 props 和 state 值的浅比较复写了 shouldComponentUpdate() 的实现。
   * 使用 `React.PureComponent` 时，更新 state 和 props 中的变量需要避免可变对象的产生。
   * 组合 React 组件时，不要将箭头函数赋值给 JSX 属性，这可能导致每次渲染都会产生一个新的函数，常见情景为函数绑定。
   * 将组件尽可能地拆分、解耦，同时不要滥用 props（只传必要的数据）。

## 十五、在使用 React Native 中遇到了什么困难

* React Native 在大多数情况下并不是完全原生，实际开发过程中还需要进行 Andiroid 配置与 Android 源码的编写。
* 不同系统提供的原生组件和 API 不一样，有些功能是某个系统独有（例如 Android 的 Toast）。

## 十六、React-Router 的跳转方式及实现原理

* React-Router 依赖 history 库，通过对 history 进行操作实现路由和跳转。
* History 分为三大类: BrowserHistory（H5 浏览器）、HashHistory（旧版浏览器）、MemoryHistory（参考实现，可用于非 DOM 环境）。
* BrowserHistory 跳转: pushState、replaceState、popstate 等。
* HashHistory 跳转: location.hash、location.replace、hashchange 等。
* 路由是 URL 和 UI 之间的映射关系，在 React-Router 中则表现为 location 和 components 之间的映射。
* React-Router 中的重要组件: Router、RouterContext、Link（用于跳转）。

## 十七、setState 是异步的吗？什么情况下需要用同步的 setState

* setState 是异步的，待更新的 state 会被放到队列中（批量）延迟更新，这样做有利于性能优化。
* 如果 state 后续状态依赖当前状态，则需要同步的 setState，方法是 seState 设置第二个参数为函数，其保证会引用更新后的state值。

## 十八、如何实现 Javascript 继承机制

* 大部分的编程语言都是通过 class 来实现对象的继承，传统的 Javascript 不通过 class，而是通过原型对象（prototype）实现。
* 构造函数生成对象: 实现方便，但同一个构造函数的多个实例之间无法共享属性，复用性低。
* Javascript 继承的思想是: 原型对象上的属性和方法，可以被所有实例对象共享，因此可以通过改写对象原型实现继承。

#### 实例的继承

* 实例可以重写原型链中的属性和方法，如果一个实例没有对应的属性和方法，就会顺着原型链一直向上寻找直到尽头（Object.prototype 的原型为 null）。
* prototype 对象有一个 constructor 属性，默认指向 prototype 的构造函数，作用是指明实例对象是由哪个构造函数产生的。
* 通常情况下，改写对象原型的同时也要修改 constructor 属性，否则只在原型上添加方法即可（而不是替换整个原型）。

#### 构造函数的继承

* 第一步是在子类的构造函数内调用父类的构造函数; 第二步是让子类的原型指向父类的原型（不可以浅复制）。
* 继承方法二: 让子类的原型等于一个父类实例（这种方法会使子类拥有父类实例的方法，不一定是我们想要的）
* 多重继承: Javascript 本身不提供多重继承的方法，但可以通过混入（Mixin）的方式实现（有风险）。

## 十九、React 在什么情况下会使用 Hook 和高阶组件

* Hook 可以在不编写 class 组件的情况下使用 state 以及其他 react 特性，在无需修改组件结构的情况下复用状态逻辑。
* 对编程模式的抽象封装，例如某个组件挂载时订阅外部数据，渲染时展示数据，卸载时取消订阅，这个常见的模式就可以用高阶组件进一步封装。
