<a name="module_perspective-viewer"></a>

## perspective-viewer
Module for `<perspective-viewer` custom element.  There are no exports from


* [perspective-viewer](#module_perspective-viewer)
    * [~PerspectiveViewer](#module_perspective-viewer..PerspectiveViewer) ⇐ <code>HTMLElement</code>
        * [new PerspectiveViewer()](#new_module_perspective-viewer..PerspectiveViewer_new)
        * [.sort](#module_perspective-viewer..PerspectiveViewer+sort) : <code>array.&lt;string&gt;</code>
        * [.columns](#module_perspective-viewer..PerspectiveViewer+columns)
        * [.computed-columns](#module_perspective-viewer..PerspectiveViewer+computed-columns)
        * [.aggregates](#module_perspective-viewer..PerspectiveViewer+aggregates)
        * [.filters](#module_perspective-viewer..PerspectiveViewer+filters) : <code>array</code>
        * [.view](#module_perspective-viewer..PerspectiveViewer+view) : <code>string</code>
        * [.column-pivots](#module_perspective-viewer..PerspectiveViewer+column-pivots) : <code>Array.&lt;String&gt;</code>
        * [.row-pivots](#module_perspective-viewer..PerspectiveViewer+row-pivots) : <code>array.&lt;string&gt;</code>
        * [.worker](#module_perspective-viewer..PerspectiveViewer+worker)
        * [.view](#module_perspective-viewer..PerspectiveViewer+view)
        * [.message(msg)](#module_perspective-viewer..PerspectiveViewer+message)
        * [.load(data)](#module_perspective-viewer..PerspectiveViewer+load) ⇒ <code>Promise.&lt;void&gt;</code>
        * [.update(data)](#module_perspective-viewer..PerspectiveViewer+update)
        * [.notifyResize()](#module_perspective-viewer..PerspectiveViewer+notifyResize)
        * [.clone(widget)](#module_perspective-viewer..PerspectiveViewer+clone)
        * [.delete()](#module_perspective-viewer..PerspectiveViewer+delete) ⇒ <code>Promise.&lt;boolean&gt;</code>
        * [.save()](#module_perspective-viewer..PerspectiveViewer+save) ⇒ <code>object</code>
        * [.restore(x)](#module_perspective-viewer..PerspectiveViewer+restore) ⇒ <code>Promise.&lt;void&gt;</code>
        * [.flush()](#module_perspective-viewer..PerspectiveViewer+flush) ⇒ <code>Promise.&lt;void&gt;</code>
        * [.clear()](#module_perspective-viewer..PerspectiveViewer+clear)
        * [.replace()](#module_perspective-viewer..PerspectiveViewer+replace)
        * [.reset()](#module_perspective-viewer..PerspectiveViewer+reset)
        * [.copy()](#module_perspective-viewer..PerspectiveViewer+copy)
        * [.toggleConfig()](#module_perspective-viewer..PerspectiveViewer+toggleConfig)


* * *

<a name="module_perspective-viewer..PerspectiveViewer"></a>

### perspective-viewer~PerspectiveViewer ⇐ <code>HTMLElement</code>
**Kind**: inner class of [<code>perspective-viewer</code>](#module_perspective-viewer)  
**Extends**: <code>HTMLElement</code>  

* [~PerspectiveViewer](#module_perspective-viewer..PerspectiveViewer) ⇐ <code>HTMLElement</code>
    * [new PerspectiveViewer()](#new_module_perspective-viewer..PerspectiveViewer_new)
    * [.sort](#module_perspective-viewer..PerspectiveViewer+sort) : <code>array.&lt;string&gt;</code>
    * [.columns](#module_perspective-viewer..PerspectiveViewer+columns)
    * [.computed-columns](#module_perspective-viewer..PerspectiveViewer+computed-columns)
    * [.aggregates](#module_perspective-viewer..PerspectiveViewer+aggregates)
    * [.filters](#module_perspective-viewer..PerspectiveViewer+filters) : <code>array</code>
    * [.view](#module_perspective-viewer..PerspectiveViewer+view) : <code>string</code>
    * [.column-pivots](#module_perspective-viewer..PerspectiveViewer+column-pivots) : <code>Array.&lt;String&gt;</code>
    * [.row-pivots](#module_perspective-viewer..PerspectiveViewer+row-pivots) : <code>array.&lt;string&gt;</code>
    * [.worker](#module_perspective-viewer..PerspectiveViewer+worker)
    * [.view](#module_perspective-viewer..PerspectiveViewer+view)
    * [.message(msg)](#module_perspective-viewer..PerspectiveViewer+message)
    * [.load(data)](#module_perspective-viewer..PerspectiveViewer+load) ⇒ <code>Promise.&lt;void&gt;</code>
    * [.update(data)](#module_perspective-viewer..PerspectiveViewer+update)
    * [.notifyResize()](#module_perspective-viewer..PerspectiveViewer+notifyResize)
    * [.clone(widget)](#module_perspective-viewer..PerspectiveViewer+clone)
    * [.delete()](#module_perspective-viewer..PerspectiveViewer+delete) ⇒ <code>Promise.&lt;boolean&gt;</code>
    * [.save()](#module_perspective-viewer..PerspectiveViewer+save) ⇒ <code>object</code>
    * [.restore(x)](#module_perspective-viewer..PerspectiveViewer+restore) ⇒ <code>Promise.&lt;void&gt;</code>
    * [.flush()](#module_perspective-viewer..PerspectiveViewer+flush) ⇒ <code>Promise.&lt;void&gt;</code>
    * [.clear()](#module_perspective-viewer..PerspectiveViewer+clear)
    * [.replace()](#module_perspective-viewer..PerspectiveViewer+replace)
    * [.reset()](#module_perspective-viewer..PerspectiveViewer+reset)
    * [.copy()](#module_perspective-viewer..PerspectiveViewer+copy)
    * [.toggleConfig()](#module_perspective-viewer..PerspectiveViewer+toggleConfig)


* * *

<a name="new_module_perspective-viewer..PerspectiveViewer_new"></a>

#### new PerspectiveViewer()
HTMLElement class for `<perspective-viewer>` custom element.  This class is

**Example**  
```js
// Create a new `<perspective-viewer>`
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+sort"></a>

#### perspectiveViewer.sort : <code>array.&lt;string&gt;</code>
Sets this `perspective.table.view`'s `sort` property, an array of column

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Emits**: <code>PerspectiveViewer#event:perspective-config-update</code>  
**Example** *(via Javascript DOM)*  
```js
let elem = document.getElementById('my_viewer');
elem.setAttribute('sort', JSON.stringify([["x","desc"]));
```
**Example** *(via HTML)*  
```js
<perspective-viewer sort='[["x","desc"]]'></perspective-viewer>
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+columns"></a>

#### perspectiveViewer.columns
The set of visible columns.

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Emits**: <code>PerspectiveViewer#event:perspective-config-update</code>  
**Params**

- columns <code>array</code> - An array of strings, the names of visible columns.

**Example** *(via Javascript DOM)*  
```js
let elem = document.getElementById('my_viewer');
elem.setAttribute('columns', JSON.stringify(["x", "y'"]));
```
**Example** *(via HTML)*  
```js
<perspective-viewer columns='["x", "y"]'></perspective-viewer>
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+computed-columns"></a>

#### perspectiveViewer.computed-columns
The set of visible columns.

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Emits**: <code>PerspectiveViewer#event:perspective-config-update</code>  
**Params**

- computed-columns <code>array</code> - An array of computed column objects

**Example** *(via Javascript DOM)*  
```js
let elem = document.getElementById('my_viewer');
elem.setAttribute('computed-columns', JSON.stringify([{name: "x+y", func: "add", inputs: ["x", "y"]}]));
```
**Example** *(via HTML)*  
```js
<perspective-viewer computed-columns="[{name:'x+y',func:'add',inputs:['x','y']}]""></perspective-viewer>
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+aggregates"></a>

#### perspectiveViewer.aggregates
The set of column aggregate configurations.

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Emits**: <code>PerspectiveViewer#event:perspective-config-update</code>  
**Params**

- aggregates <code>object</code> - A dictionary whose keys are column names, and

**Example** *(via Javascript DOM)*  
```js
let elem = document.getElementById('my_viewer');
elem.setAttribute('aggregates', JSON.stringify({x: "distinct count"}));
```
**Example** *(via HTML)*  
```js
<perspective-viewer aggregates='{"x": "distinct count"}'></perspective-viewer>
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+filters"></a>

#### perspectiveViewer.filters : <code>array</code>
The set of column filter configurations.

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Emits**: <code>PerspectiveViewer#event:perspective-config-update</code>  
**Example** *(via Javascript DOM)*  
```js
let filters = [
    ["x", "<", 3],
    ["y", "contains", "abc"]
];
let elem = document.getElementById('my_viewer');
elem.setAttribute('filters', JSON.stringify(filters));
```
**Example** *(via HTML)*  
```js
<perspective-viewer filters='[["x", "<", 3], ["y", "contains", "abc"]]'></perspective-viewer>
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+view"></a>

#### perspectiveViewer.view : <code>string</code>
Sets the currently selected plugin, via its `name` field.

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Emits**: <code>PerspectiveViewer#event:perspective-config-update</code>  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+column-pivots"></a>

#### perspectiveViewer.column-pivots : <code>Array.&lt;String&gt;</code>
Sets this `perspective.table.view`'s `column_pivots` property.

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Emits**: <code>PerspectiveViewer#event:perspective-config-update</code>  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+row-pivots"></a>

#### perspectiveViewer.row-pivots : <code>array.&lt;string&gt;</code>
Sets this `perspective.table.view`'s `row_pivots` property.

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Emits**: <code>PerspectiveViewer#event:perspective-config-update</code>  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+worker"></a>

#### perspectiveViewer.worker
This element's `perspective` worker instance.  This property is not

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Read only**: true  
**Example**  
```js
let elem = document.getElementById('my_viewer');
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+view"></a>

#### perspectiveViewer.view
This element's `perspective.table.view` instance.  The instance itself

**Kind**: instance property of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Read only**: true  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+message"></a>

#### perspectiveViewer.message(msg)
When set, hide the data visualization and display the message.  Setting

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Params**

- msg <code>string</code> - The message. This can be HTML - it is not sanitized.

**Example**  
```js
let elem = document.getElementById('my_viewer');
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+load"></a>

#### perspectiveViewer.load(data) ⇒ <code>Promise.&lt;void&gt;</code>
Load data.  If `load` or `update` have already been called on this

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Returns**: <code>Promise.&lt;void&gt;</code> - A promise which resolves once the data is
**Emits**: <code>module:perspective\_viewer~PerspectiveViewer#perspective-click PerspectiveViewer#event:perspective-view-update</code>  
**Params**

- data <code>any</code> - The data to load.  Works with the same input types

**Example** *(Load JSON)*  
```js
const my_viewer = document.getElementById('#my_viewer');
my_viewer.load([
    {x: 1, y: 'a'},
    {x: 2, y: 'b'}
]);
```
**Example** *(Load CSV)*  
```js
const my_viewer = document.getElementById('#my_viewer');
my_viewer.load("x,y\n1,a\n2,b");
```
**Example** *(Load perspective.table)*  
```js
const my_viewer = document.getElementById('#my_viewer');
const tbl = perspective.table("x,y\n1,a\n2,b");
my_viewer.load(tbl);
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+update"></a>

#### perspectiveViewer.update(data)
Updates this element's `perspective.table` with new data.

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Emits**: <code>PerspectiveViewer#event:perspective-view-update</code>  
**Params**

- data <code>any</code> - The data to load.  Works with the same input types

**Example**  
```js
const my_viewer = document.getElementById('#my_viewer');
```

* * *

<a name="module_perspective-viewer..PerspectiveViewer+notifyResize"></a>

#### perspectiveViewer.notifyResize()
Determine whether to reflow the viewer and redraw.

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+clone"></a>

#### perspectiveViewer.clone(widget)
Duplicate an existing `<perspective-element>`, including data and view

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Params**

- widget <code>any</code> - A `<perspective-viewer>` instance to clone.


* * *

<a name="module_perspective-viewer..PerspectiveViewer+delete"></a>

#### perspectiveViewer.delete() ⇒ <code>Promise.&lt;boolean&gt;</code>
Deletes this element's data and clears it's internal state (but not its

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Returns**: <code>Promise.&lt;boolean&gt;</code> - Whether or not this call resulted in the

* * *

<a name="module_perspective-viewer..PerspectiveViewer+save"></a>

#### perspectiveViewer.save() ⇒ <code>object</code>
Serialize this element's attribute/interaction state.

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Returns**: <code>object</code> - a serialized element.  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+restore"></a>

#### perspectiveViewer.restore(x) ⇒ <code>Promise.&lt;void&gt;</code>
Restore this element to a state as generated by a reciprocal call to

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Returns**: <code>Promise.&lt;void&gt;</code> - A promise which resolves when the changes have
**Params**

- x <code>object</code> - returned by `save`.


* * *

<a name="module_perspective-viewer..PerspectiveViewer+flush"></a>

#### perspectiveViewer.flush() ⇒ <code>Promise.&lt;void&gt;</code>
Flush any pending attribute modifications to this element.

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  
**Returns**: <code>Promise.&lt;void&gt;</code> - A promise which resolves when the current

* * *

<a name="module_perspective-viewer..PerspectiveViewer+clear"></a>

#### perspectiveViewer.clear()
Clears the rows in the current [table](table).

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+replace"></a>

#### perspectiveViewer.replace()
Replaces all rows in the current [table](table).

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+reset"></a>

#### perspectiveViewer.reset()
Reset's this element's view state and attributes to default.  Does not

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+copy"></a>

#### perspectiveViewer.copy()
Copies this element's view data (as a CSV) to the clipboard.  This method

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  

* * *

<a name="module_perspective-viewer..PerspectiveViewer+toggleConfig"></a>

#### perspectiveViewer.toggleConfig()
Opens/closes the element's config menu.

**Kind**: instance method of [<code>PerspectiveViewer</code>](#module_perspective-viewer..PerspectiveViewer)  

* * *
