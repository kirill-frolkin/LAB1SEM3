package queue

type Queue struct {
	Data []string
}

func New() *Queue { return &Queue{Data: make([]string, 0)} }

func (q *Queue) Enqueue(val string) {
	q.Data = append(q.Data, val)
}

func (q *Queue) Dequeue() string {
	if len(q.Data) == 0 {
		return ""
	}
	val := q.Data[0]
	q.Data = q.Data[1:]
	return val
}

func (q *Queue) Front() string {
	if len(q.Data) == 0 {
		return ""
	}
	return q.Data[0]
}
