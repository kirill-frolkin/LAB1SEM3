package dlist

type Node struct {
	Key  string
	Prev *Node
	Next *Node
}

type List struct {
	Head *Node
	Tail *Node
}

func New() *List { return &List{} }

func (l *List) PushHead(key string) {
	newNode := &Node{Key: key, Prev: nil, Next: l.Head}
	if l.Head != nil {
		l.Head.Prev = newNode
	} else {
		l.Tail = newNode
	}
	l.Head = newNode
}

func (l *List) PushTail(key string) {
	newNode := &Node{Key: key, Prev: l.Tail, Next: nil}
	if l.Tail != nil {
		l.Tail.Next = newNode
	} else {
		l.Head = newNode
	}
	l.Tail = newNode
}

func (l *List) PopHead() string {
	if l.Head == nil {
		return ""
	}
	val := l.Head.Key
	l.Head = l.Head.Next
	if l.Head != nil {
		l.Head.Prev = nil
	} else {
		l.Tail = nil
	}
	return val
}

func (l *List) PopTail() string {
	if l.Tail == nil {
		return ""
	}
	val := l.Tail.Key
	l.Tail = l.Tail.Prev
	if l.Tail != nil {
		l.Tail.Next = nil
	} else {
		l.Head = nil
	}
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
	curr := l.Head
	for curr != nil {
		if curr.Key == key {
			if curr.Prev != nil {
				curr.Prev.Next = curr.Next
			} else {
				l.Head = curr.Next
			}
			if curr.Next != nil {
				curr.Next.Prev = curr.Prev
			} else {
				l.Tail = curr.Prev
			}
			return
		}
		curr = curr.Next
	}
}
