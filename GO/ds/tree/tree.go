package tree

type Node struct {
	Data  string
	Left  *Node
	Right *Node
}

type Tree struct {
	Root *Node
}

func New() *Tree { return &Tree{} }

func (t *Tree) Insert(val string) {
	newNode := &Node{Data: val}
	if t.Root == nil {
		t.Root = newNode
		return
	}
	q := []*Node{t.Root}
	for len(q) > 0 {
		curr := q[0]
		q = q[1:]
		if curr.Left == nil {
			curr.Left = newNode
			break
		} else {
			q = append(q, curr.Left)
		}
		if curr.Right == nil {
			curr.Right = newNode
			break
		} else {
			q = append(q, curr.Right)
		}
	}
}

func (t *Tree) Find(val string) bool {
	if t.Root == nil {
		return false
	}
	q := []*Node{t.Root}
	for len(q) > 0 {
		curr := q[0]
		q = q[1:]
		if curr.Data == val {
			return true
		}
		if curr.Left != nil {
			q = append(q, curr.Left)
		}
		if curr.Right != nil {
			q = append(q, curr.Right)
		}
	}
	return false
}

func (t *Tree) IsComplete() bool {
	if t.Root == nil {
		return true
	}
	q := []*Node{t.Root}
	nullFound := false
	for len(q) > 0 {
		curr := q[0]
		q = q[1:]
		if curr == nil {
			nullFound = true
		} else {
			if nullFound {
				return false
			}
			q = append(q, curr.Left, curr.Right)
		}
	}
	return true
}
