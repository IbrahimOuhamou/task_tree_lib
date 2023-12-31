--بسم الله الرحمن الرحيم

print("[lua] alhamdo li Allah. called he file 'task_tree.lua'")

task_tree = {}

--defines the functions declared here
--task_tree.task = {}

--returns a new task pointer with this name
task_tree.task_new = function(name) print('Allah Akbar') return "name" end

--returns the name of a task
task_tree.task_get_name = function(task) return "default" end

--frees the {task}
task_tree.task_free = function(task) end

return task_tree

