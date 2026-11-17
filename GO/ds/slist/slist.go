package slist

type Node struct {
	Key  string
	Next *Node
}

type List struct {
	Head *Node
	Tail *Node
}

func New() *List { return &List{} }

func (l *List) PushHead(key string) {
	newNode := &Node{Key: key, Next: l.Head}
	l.Head = newNode
	if l.Tail == nil {
		l.Tail = newNode
	}
}

func (l *List) PushTail(key string) {
	newNode := &Node{Key: key, Next: nil}
	if l.Tail == nil {
		l.Head = newNode
		l.Tail = newNode
	} else {
		l.Tail.Next = newNode
		l.Tail = newNode
	}
}

func (l *List) PopHead() string {
	if l.Head == nil {
		return ""
	}
	val := l.Head.Key
	l.Head = l.Head.Next
	if l.Head == nil {
		l.Tail = nil
	}
	return val
}

func (l *List) PopTail() string {
	if l.Head == nil {
		return ""
	}
	if l.Head == l.Tail {
		return l.PopHead()
	}
	curr := l.Head
	for curr.Next != l.Tail {
		curr = curr.Next
	}
	val := l.Tail.Key
	l.Tail = curr
	l.Tail.Next = nil
	return val
}

func (l *List) Get(key string) bool {
	curr := l.Head
	for curr != nil {
		if curr.Key == key {
			return true
		}
		curr = curr.Next
	}
	return false
}

func (l *List) Del(key string) {
	if l.Head == nil {
		return
	}
	if l.Head.Key == key {
		l.PopHead()
		return
	}
	curr := l.Head
	for curr.Next != nil && curr.Next.Key != key {
		curr = curr.Next
	}
	if curr.Next != nil {
		temp := curr.Next
		curr.Next = temp.Next
		if temp == l.Tail {
			l.Tail = curr
		}
	}
}
