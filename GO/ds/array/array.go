package array

type Array struct {
	Data []string
}

func New() *Array {
	return &Array{Data: make([]string, 0)}
}

func (a *Array) PushBack(val string) {
	a.Data = append(a.Data, val)
}

func (a *Array) PushFront(val string) {
	a.Data = append([]string{val}, a.Data...)
}

func (a *Array) PopBack() {
	if len(a.Data) > 0 {
		a.Data = a.Data[:len(a.Data)-1]
	}
}

func (a *Array) PopFront() {
	if len(a.Data) > 0 {
		a.Data = a.Data[1:]
	}
}

func (a *Array) Get(idx int) string {
	if idx >= 0 && idx < len(a.Data) {
		return a.Data[idx]
	}
	return ""
}

func (a *Array) Del(idx int) {
	if idx >= 0 && idx < len(a.Data) {
		a.Data = append(a.Data[:idx], a.Data[idx+1:]...)
	}
}
