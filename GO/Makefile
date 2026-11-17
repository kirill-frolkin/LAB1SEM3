TARGET = dbms

all: build

build:
	go build -o $(TARGET) .

clean:
	rm -f $(TARGET) file.data

# Автоматическая проверка контрольных примеров по методичке (на Go)
test: build
	@echo "=== 1. Добавление элемента 'item' в стек 'mystack' ==="
	./$(TARGET) --file file.data --query 'SPUSH mystack item'
	
	@echo "\n=== 2. Чтение и удаление элемента из очереди 'myqueue' ==="
	./$(TARGET) --file file.data --query 'QPUSH myqueue element' > /dev/null
	./$(TARGET) --file file.data --query 'QPOP myqueue'
	
	@echo "\n=== 3. Проверка дерева 'mytree' (Complete Binary Tree) ==="
	./$(TARGET) --file file.data --query 'TINSERT mytree value' > /dev/null
	./$(TARGET) --file file.data --query 'ISMEMBER mytree value'
	./$(TARGET) --file file.data --query 'TCOMPLETE mytree'
	
	@echo "\n=== 4. Итоговое состояние базы данных (file.data) ==="
	@cat file.data
