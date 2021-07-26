# 链表（List）

通过“指针”将一组零散的内存块串联起来使用。

## 常见分类

### 单链表

```C++
struct Node{
    int data;
    struct Node* next;
}
```

由 Node 节点串联的数据结构。其中有两个结点是比较特殊的，它们分别是第一个结点和最后一个结点。我们习惯性地把第一个结点叫作头结点，把最后一个结点叫作尾结点。其中，头结点用来记录链表的基地址。有了它，我们就可以遍历得到整条链表。而尾结点特殊的地方是：指针不是指向下一个结点，而 是指向一个空地址 NULL，表示这是链表上最后一个结点。

### 循环链表

它跟单链表唯一的区别就在尾结点。我们知道，单链表的尾结点指针指向空地址，表示这就是最后 的结点了。而循环链表的尾结点指针是指向链表的头结点。

### 双向链表

```C++
struct Node{
    int data;
    struct Node* pre;
    struct Node* next;
}
```

双向链表需要额外的两个空间来存储后继结点和前驱结点的地址。

## 常见例题

### 单链表反转

[LeetCode 206](https://leetcode-cn.com/problems/reverse-linked-list/)

<!-- tabs:start -->

#### **C++**

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// 迭代实现
ListNode* reverseList(ListNode* head) {
    if (head == NULL) {
        return 
    }
    ListNode* cur = head;
    ListNode* pre = NULL;
    ListNode* next = NULL;
    while(cur != NULL) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}

// 递归实现
 ListNode* reverseList(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    ListNode* newHead = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}
```

#### **Kotlin**

```kotlin
/**
 * Example:
 * var li = ListNode(5)
 * var v = li.`val`
 * Definition for singly-linked list.
 * class ListNode(var `val`: Int) {
 *     var next: ListNode? = null
 * }
 */

// 迭代实现
fun reverseList(head: ListNode?): ListNode? {
    if (head == null) {
        return head;
    }
    var cur: ListNode? = head
    var pre: ListNode? = null
    var next: ListNode? = null
    while(cur != null) {
        next = cur.next
        cur.next = pre
        pre = cur
        cur = next
    }
    return pre
}

// 递归实现
fun reverseList(head: ListNode?): ListNode? {
    if (head == null || head.next == null) {
        return head
    }
    val newHead: ListNode? = reverseList(head.next)
    head.next.next = head
    head.next = null
    return newHead
}
```

<!-- tabs:end -->

### 单链表区间反转

[LeetCode 92](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

<!-- tabs:start -->

#### **C++**

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (head == NULL) {
        return head;
    }
    ListNode* cur = head;
    ListNode* pre = NULL; 
    ListNode* next = NULL;
    ListNode* start = NULL;
    ListNode* end = NULL;
    int index = 1;
    while(index < left && cur != NULL){
        pre = cur;
        index++;
        cur = cur->next;
    }
    if (cur == NULL || cur->next == NULL) {
        return head;
    }
    start = pre;
    end = cur;
    while(index <= right && cur != NULL) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
        index++;
    }
    if (end != NULL) {
        end->next = cur;
    }
    if (start != NULL) {
        start->next = pre;
        return head;
    } else {
        return pre;
    }
}
```

#### **Kotlin**

```kotlin
/**
 * Example:
 * var li = ListNode(5)
 * var v = li.`val`
 * Definition for singly-linked list.
 * class ListNode(var `val`: Int) {
 *     var next: ListNode? = null
 * }
 */

fun reverseBetween(head: ListNode?, left: Int, right: Int): ListNode? {
    if (head == null) {
        return head
    }
    var cur :ListNode? = head
    var pre :ListNode? = null
    var next :ListNode?= null
    var start :ListNode? = null
    var end :ListNode? = null
    var index = 1
    while (index < left && cur != null) {
        pre = cur
        index++
        cur = cur.next
    }
    if (cur == null || cur.next == null) {
        return head
    }
    start = pre
    end = cur
    while (index <= right && cur != null) {
        next = cur.next
        cur.next = pre
        pre = cur
        cur = next
        index++
    }
    if (end != null) {
        end.next = cur
    }
    if (start != null) {
        start.next = pre
        return head
    } else {
        return pre
    }
}
```

<!-- tabs:end -->

### k个一组反转链表

[LeetCode](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

<!-- tabs:start -->

#### **C++**

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

 ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == NULL) {
        return head;
    }
    ListNode* start = head;
    ListNode* end = head;
    for (int i = 0; i< k; i++) {
        if (end == NULL) {
            return head;
        }
        end = end->next;
    }
    ListNode* newHead = reverse(start, end);
    start->next = reverseKGroup(end, k);
    return newHead;
}

ListNode* reverse(ListNode* head, ListNode* tail) {
    ListNode* cur = head;
    ListNode* pre = NULL;
    ListNode* next = NULL;
    while (cur != tail) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}
```

#### **Kotlin**

```kotlin
/**
 * Example:
 * var li = ListNode(5)
 * var v = li.`val`
 * Definition for singly-linked list.
 * class ListNode(var `val`: Int) {
 *     var next: ListNode? = null
 * }
 */

fun reverseKGroup(head: ListNode?, k: Int): ListNode? {
    if (head == null) {
        return head
    }
    var start: ListNode? = head
    var end: ListNode? = head
    for (i in 1..k) {
        if (end == null) {
            return head
        }
        end = end.next
    }
    var newHead: ListNode? = reverse(start, end)
    start?.next = reverseKGroup(end, k)
    return newHead;
}

fun reverse(head: ListNode?, tail: ListNode?): ListNode? {
    var cur :ListNode? = head
    var pre :ListNode? = null
    var next :ListNode? = null
    while (cur != tail) {
        next = cur?.next
        cur?.next = pre
        pre = cur
        cur = next
    }
    return pre
}
```

<!-- tabs:end -->

### 链表中环的检测

LeetCode 141

### 两个有序的链表合并

LeetCode 21

### 删除链表倒数第 n 个结点

LeetCode 19

### 求链表的中间结点

LeetCode 876
