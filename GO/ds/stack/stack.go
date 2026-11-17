package stack

type Stack struct {
	Data []string
}

func New() *Stack { return &Stack{Data: make([]string, 0)} }

func (s *Stack) Push(val string) {
	s.Data = append(s.Data, val)
}

func (s *Stack) Pop() string {
	if len(s.Data) == 0 {
		return ""
	}
	idx := len(s.Data) - 1
	val := s.Data[idx]
	s.Data = s.Data[:idx]
	return val
}

func (s *Stack) Peek() string {
	if len(s.Data) == 0 {
		return ""
	}
	return s.Data[len(s.Data)-1]
}
