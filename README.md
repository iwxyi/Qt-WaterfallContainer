瀑布流控件
===

简单易用的 Qt 瀑布流控件，不只能添加图片，还支持任意类型控件。

并且允许添加**不规则宽高**的控件，比一般的多列瀑布流更加自由。

## 功能

- 相同列宽模式
  - 自动调整列数，或者固定列数
  - 统一根据 `sizeHint` 调整大小
  - 统一根据最大控件宽度调整大小
- 不规则宽高模式
  - 支持任意宽高
  - 自动调整排列
- 动态添加控件，计算位置
- 自定义边距、间距
- 批量非线性动画，可开关
- 平滑滚动



![相同宽度的瀑布流](screenshots/瀑布流_相同宽度.gif)

![不规则宽高的瀑布流](screenshots/瀑布流_不规则宽高.gif)



## 用法

可参考 `mainwindow` 中的代码。

### 创建

- 方法一：`new WaterfallScrollArea`
- 方法二：`UI Designer` 中添加 `QScrollArea`，提升为 `WaterfallScrollArea`

### 模式

默认为相同列宽（即普通的瀑布流），通过下面方法切换：

``` C++
setAllowDifferentWidth(true);
```

### 设置列数

```C++
setFixedColCount(col);
```

相同列宽模式时，可用来固定列数；

否则将会根据本身的宽度与其子控件的宽度，自动选择合适的列数。

修改模式或任意内容后，通过 `adjustWidgetsPos()` 来更新所有子控件的位置。

### 调整大小

```C++
// 统一设置为相同宽度
// 如果未固定列数，默认为子控件中最大的一个宽度
// 若固定列数，则约为scrollArea的宽度/列数
resizeWidgetsToEqualWidth();

// 统一设置为 sizeHint 大小
resizeWidgetsToSizeHint();
```

### 调整位置

在切换模式、调整控件大小时，为保证多步操作的性能，不会立刻调整所有子控件的位置

所以需要**手动调用**以下代码，来更新子控件的坐标：

```C++
adjustWidgetsPos(); // 需要手动调用
```

在改变 ScrollArea 的大小的时候，会自动调用，无需开发者关心。

### 动态创建子控件

```C++
new QWidget(ui->scrollArea->widget());
```

注意创建的 `parent` **必须为** `scrollArea->widget()`，否则将无法为其调整位置。

### 只初始化一次

在某些情况下，瀑布流中的实例对象是固定的（如作为设置页面，不会动态添加子控件），可在所有控件创建完毕之后，调用一下代码：

```C++
initFixedChildren();
```

在之后的 `resizeEvent`、`adjustWidgetsPos` 等，**不会重复更新控件**，得以提升性能。

若后续可能会动态添加子控件，每次添加之后，需要调用 `addWidget(QWidget*)` 放入合适的位置，或者调用 `updateChildWidgets()` 刷新所有子控件，并再次更新所有子控件的位置。