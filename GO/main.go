package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"

	"lab1-go/ds/array"
	"lab1-go/ds/dlist"
	"lab1-go/ds/queue"
	"lab1-go/ds/slist"
	"lab1-go/ds/stack"
	"lab1-go/ds/tree"
)

func boolToStr(val bool) string {
	if val {
		return "TRUE"
	}
	return "FALSE"
}

func main() {
	var filename, query string
	for i := 1; i < len(os.Args); i++ {
		if os.Args[i] == "--file" && i+1 < len(os.Args) {
			filename = os.Args[i+1]
			i++
		} else if os.Args[i] == "--query" && i+1 < len(os.Args) {
			query = os.Args[i+1]
			i++
		}
	}

	if filename == "" || query == "" {
		fmt.Println("Usage: go run . --file <file.data> --query '<COMMAND> <STRUCT_NAME> [ARGS...]'")
		os.Exit(1)
	}

	arrays := make(map[string]*array.Array)
	slists := make(map[string]*slist.List)
	dlists := make(map[string]*dlist.List)
	stacks := make(map[string]*stack.Stack)
	queues := make(map[string]*queue.Queue)
	trees := make(map[string]*tree.Tree)

	// 1. Deserialization
	data, err := os.ReadFile(filename)
	if err == nil {
		lines := strings.Split(string(data), "\n")
		for _, line := range lines {
			line = strings.TrimSpace(line)
			if line == "" {
				continue
			}
			fields := strings.Fields(line)
			if len(fields) < 2 {
				continue
			}
			typeStr := fields[0]
			name := fields[1]
			vals := fields[2:]

			switch typeStr {
			case "ARRAY":
				arrays[name] = array.New()
				for _, v := range vals {
					arrays[name].PushBack(v)
				}
			case "SLIST":
				slists[name] = slist.New()
				for _, v := range vals {
					slists[name].PushTail(v)
				}
			case "DLIST":
				dlists[name] = dlist.New()
				for _, v := range vals {
					dlists[name].PushTail(v)
				}
			case "STACK":
				stacks[name] = stack.New()
				for _, v := range vals {
					stacks[name].Push(v)
				}
			case "QUEUE":
				queues[name] = queue.New()
				for _, v := range vals {
					queues[name].Enqueue(v)
				}
			case "TREE":
				trees[name] = tree.New()
				for _, v := range vals {
					trees[name].Insert(v)
				}
			}
		}
	}

	// 2. Execute Query
	qs := strings.Fields(query)
	if len(qs) < 2 {
		os.Exit(0)
	}
	cmd := qs[0]

	// ARRAY (M)
	if cmd == "MPUSH" && len(qs) >= 4 {
		dir, name, val := qs[1], qs[2], qs[3]
		if arrays[name] == nil { arrays[name] = array.New() }
		if dir == "F" { arrays[name].PushFront(val) } else { arrays[name].PushBack(val) }
		fmt.Println("->", val)
	} else if cmd == "MPOP" && len(qs) >= 3 {
		dir, name := qs[1], qs[2]
		if arrays[name] != nil {
			if dir == "F" { arrays[name].PopFront() } else { arrays[name].PopBack() }
		}
	} else if cmd == "MGET" && len(qs) >= 3 {
		name := qs[1]
		idx, _ := strconv.Atoi(qs[2])
		if arrays[name] != nil { fmt.Println("->", arrays[name].Get(idx)) }
	} else if cmd == "MDEL" && len(qs) >= 3 {
		name := qs[1]
		idx, _ := strconv.Atoi(qs[2])
		if arrays[name] != nil { arrays[name].Del(idx) }
	} else 
	// SINGLY LINKED LIST (F)
	if cmd == "FPUSH" && len(qs) >= 4 {
		dir, name, val := qs[1], qs[2], qs[3]
		if slists[name] == nil { slists[name] = slist.New() }
		if dir == "F" { slists[name].PushHead(val) } else { slists[name].PushTail(val) }
		fmt.Println("->", val)
	} else if cmd == "FPOP" && len(qs) >= 3 {
		dir, name := qs[1], qs[2]
		if slists[name] != nil {
			var res string
			if dir == "F" { res = slists[name].PopHead() } else { res = slists[name].PopTail() }
			fmt.Println("->", res)
		}
	} else if cmd == "FGET" && len(qs) >= 3 {
		name, val := qs[1], qs[2]
		if slists[name] != nil { fmt.Println("->", boolToStr(slists[name].Get(val))) } else { fmt.Println("-> FALSE") }
	} else if cmd == "FDEL" && len(qs) >= 3 {
		name, val := qs[1], qs[2]
		if slists[name] != nil { slists[name].Del(val) }
	} else
	// DOUBLY LINKED LIST (L)
	if cmd == "LPUSH" && len(qs) >= 4 {
		dir, name, val := qs[1], qs[2], qs[3]
		if dlists[name] == nil { dlists[name] = dlist.New() }
		if dir == "F" { dlists[name].PushHead(val) } else { dlists[name].PushTail(val) }
		fmt.Println("->", val)
	} else if cmd == "LPOP" && len(qs) >= 3 {
		dir, name := qs[1], qs[2]
		if dlists[name] != nil {
			var res string
			if dir == "F" { res = dlists[name].PopHead() } else { res = dlists[name].PopTail() }
			fmt.Println("->", res)
		}
	} else if cmd == "LGET" && len(qs) >= 3 {
		name, val := qs[1], qs[2]
		if dlists[name] != nil { fmt.Println("->", boolToStr(dlists[name].Get(val))) } else { fmt.Println("-> FALSE") }
	} else if cmd == "LDEL" && len(qs) >= 3 {
		name, val := qs[1], qs[2]
		if dlists[name] != nil { dlists[name].Del(val) }
	} else
	// STACK (S)
	if cmd == "SPUSH" && len(qs) >= 3 {
		name, val := qs[1], qs[2]
		if stacks[name] == nil { stacks[name] = stack.New() }
		stacks[name].Push(val)
		fmt.Println("->", val)
	} else if cmd == "SPOP" && len(qs) >= 2 {
		name := qs[1]
		if stacks[name] != nil { fmt.Println("->", stacks[name].Pop()) }
	} else if cmd == "SPEEK" && len(qs) >= 2 {
		name := qs[1]
		if stacks[name] != nil { fmt.Println("->", stacks[name].Peek()) }
	} else
	// QUEUE (Q)
	if cmd == "QPUSH" && len(qs) >= 3 {
		name, val := qs[1], qs[2]
		if queues[name] == nil { queues[name] = queue.New() }
		queues[name].Enqueue(val)
		fmt.Println("->", val)
	} else if cmd == "QPOP" && len(qs) >= 2 {
		name := qs[1]
		if queues[name] != nil { fmt.Println("->", queues[name].Dequeue()) }
	} else if cmd == "QFRONT" && len(qs) >= 2 {
		name := qs[1]
		if queues[name] != nil { fmt.Println("->", queues[name].Front()) }
	} else
	// TREE (T)
	if cmd == "TINSERT" && len(qs) >= 3 {
		name, val := qs[1], qs[2]
		if trees[name] == nil { trees[name] = tree.New() }
		trees[name].Insert(val)
		fmt.Println("->", val)
	} else if (cmd == "TFIND" || cmd == "ISMEMBER") && len(qs) >= 3 {
		name, val := qs[1], qs[2]
		if trees[name] != nil { fmt.Println("->", boolToStr(trees[name].Find(val))) } else { fmt.Println("-> FALSE") }
	} else if cmd == "TCOMPLETE" && len(qs) >= 2 {
		name := qs[1]
		if trees[name] != nil { fmt.Println("->", boolToStr(trees[name].IsComplete())) } else { fmt.Println("-> TRUE") }
	}

	// 3. Serialization
	outFile, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error saving file:", err)
		return
	}
	defer outFile.Close()

	for name, arr := range arrays {
		outFile.WriteString("ARRAY " + name)
		for _, v := range arr.Data { outFile.WriteString(" " + v) }
		outFile.WriteString("\n")
	}
	for name, l := range slists {
		outFile.WriteString("SLIST " + name)
		curr := l.Head
		for curr != nil {
			outFile.WriteString(" " + curr.Key)
			curr = curr.Next
		}
		outFile.WriteString("\n")
	}
	for name, l := range dlists {
		outFile.WriteString("DLIST " + name)
		curr := l.Head
		for curr != nil {
			outFile.WriteString(" " + curr.Key)
			curr = curr.Next
		}
		outFile.WriteString("\n")
	}
	for name, s := range stacks {
		outFile.WriteString("STACK " + name)
		for _, v := range s.Data { outFile.WriteString(" " + v) }
		outFile.WriteString("\n")
	}
	for name, q := range queues {
		outFile.WriteString("QUEUE " + name)
		for _, v := range q.Data { outFile.WriteString(" " + v) }
		outFile.WriteString("\n")
	}
	for name, t := range trees {
		outFile.WriteString("TREE " + name)
		if t.Root != nil {
			q := []*tree.Node{t.Root}
			for len(q) > 0 {
				curr := q[0]
				q = q[1:]
				outFile.WriteString(" " + curr.Data)
				if curr.Left != nil { q = append(q, curr.Left) }
				if curr.Right != nil { q = append(q, curr.Right) }
			}
		}
		outFile.WriteString("\n")
	}
}
