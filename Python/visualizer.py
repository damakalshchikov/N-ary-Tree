import pydot


def draw_tree(nodes, path, output_png="../Images/tree.png"):
    """
    Создаёт изображение n-арного дерева с выделенным найденный путём

    :param nodes: - список узлов дерева
    :param path: - путь для сохранения изображения
    :param output_png: - список значений узлов, составляющих найденный путь с нечётными значениями
    :return: путь к сохранённому изображению
    """
    # Граф n-арного дерева
    graph = pydot.Dot(graph_type="graph", rankdir="TR")

    # Отслеживаем индексы узлов в найденном пути
    path_node_indices = []

    if path:
        # Найти индексы узлов, которые соответствуют значениям в пути
        # с учетом порядка следования в пути
        current_index = 0  # Начинаем с корня
        path_node_indices.append(current_index)

        # Для каждого следующего значения в пути находим соответствующий дочерний узел
        for i in range(1, len(path)):
            current_node = nodes[current_index]
            if current_node is None:
                break

            found = False
            for j in range(current_node["arity"]):
                child_key = f"child{j}"
                if child_key in current_node and current_node[child_key] is not None:
                    child_index = current_node[child_key]
                    if nodes[child_index] is not None and nodes[child_index]["number"] == path[i]:
                        path_node_indices.append(child_index)
                        current_index = child_index
                        found = True
                        break

            if not found:
                # Если не найден прямой потомок, выполняем поиск в ширину
                queue = []
                for j in range(current_node["arity"]):
                    child_key = f"child{j}"
                    if child_key in current_node and current_node[child_key] is not None:
                        queue.append(current_node[child_key])

                while queue and not found:
                    next_index = queue.pop(0)
                    if nodes[next_index] is not None and nodes[next_index]["number"] == path[i]:
                        path_node_indices.append(next_index)
                        current_index = next_index
                        found = True
                        break

                    next_node = nodes[next_index]
                    if next_node is not None:
                        for j in range(next_node["arity"]):
                            child_key = f"child{j}"
                            if child_key in next_node and next_node[child_key] is not None:
                                queue.append(next_node[child_key])

    # Добавляем узлы в граф
    for i, node in enumerate(nodes):
        if node is not None:
            node_value = node["number"]
            fillcolor = "lightblue"

            # Проверяем, входит ли индекс узла в путь
            if i in path_node_indices:
                fillcolor = "lightgreen"

            graph_node = pydot.Node(
                str(i), label=str(node_value), shape="circle",
                style="filled", fillcolor=fillcolor,
            )
            graph.add_node(graph_node)

            # Добавляем рёбра в граф
            for j in range(node["arity"]):
                child_key = f"child{j}"
                if child_key in node and node[child_key] is not None:
                    child = node[child_key]

                    edge_color = "black"
                    edge_width = "1.0"

                    # Проверяем, является ли ребро частью пути
                    if i in path_node_indices and child in path_node_indices:
                        idx1 = path_node_indices.index(i)
                        idx2 = path_node_indices.index(child)
                        if abs(idx1 - idx2) == 1:  # Смежные узлы в пути
                            edge_color = "green"
                            edge_width = "2.0"

                    edge = pydot.Edge(
                        str(i), str(child), dir="none",
                        color=edge_color, penwidth=edge_width,
                    )
                    graph.add_edge(edge)

    graph.write_png(output_png)
    return output_png