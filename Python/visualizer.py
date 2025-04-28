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


def draw_tree_with_multiple_paths(nodes, paths, output_png="../Images/tree_paths.png"):
    """
    Создаёт изображение n-арного дерева с выделенными путями

    :param nodes: - список узлов дерева
    :param paths: - список путей (каждый путь - список значений узлов)
    :param output_png: - путь для сохранения изображения
    :return: путь к сохранённому изображению
    """
    # Граф n-арного дерева
    graph = pydot.Dot(graph_type="graph", rankdir="TR")

    # Список цветов для разных путей
    path_colors = ["green", "blue", "red", "purple", "orange", "darkgreen", "navy", "maroon"]

    # Отслеживаем индексы узлов для каждого пути
    all_path_indices = []

    for path_idx, path in enumerate(paths):
        path_node_indices = []

        if path:
            # Найти индексы узлов в текущем пути
            current_index = 0  # Начинаем с корня
            path_node_indices.append(current_index)

            for i in range(1, len(path)):
                current_node = nodes[current_index]
                if current_node is None:
                    break

                found = False
                # Сначала ищем среди прямых потомков
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

        all_path_indices.append(path_node_indices)

    # Добавляем узлы в граф
    node_in_paths = {}  # Словарь для отслеживания, в каких путях участвует каждый узел

    # Сначала инициализируем словарь для каждого узла
    for i, node in enumerate(nodes):
        if node is not None:
            node_in_paths[i] = []

    # Теперь заполняем словарь, указывая индексы путей, в которых участвует каждый узел
    for path_idx, path_indices in enumerate(all_path_indices):
        for node_idx in path_indices:
            if node_idx in node_in_paths:
                node_in_paths[node_idx].append(path_idx)

    # Создаем узлы графа
    for i, node in enumerate(nodes):
        if node is not None:
            node_value = node["number"]
            fillcolor = "lightblue"

            # Если узел входит в какой-либо путь, делаем его заметным
            if i in node_in_paths and node_in_paths[i]:
                # Если узел входит только в один путь
                if len(node_in_paths[i]) == 1:
                    path_idx = node_in_paths[i][0]
                    color_idx = path_idx % len(path_colors)
                    fillcolor = "light" + path_colors[color_idx] if path_colors[color_idx] != "orange" else "lightsalmon"
                else:
                    # Если узел входит в несколько путей, делаем его желтым (пересечение)
                    fillcolor = "yellow"

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

                    # Проверяем, является ли ребро частью какого-либо пути
                    edge_in_paths = []
                    for path_idx, path_indices in enumerate(all_path_indices):
                        if i in path_indices and child in path_indices:
                            idx1 = path_indices.index(i)
                            idx2 = path_indices.index(child)
                            if abs(idx1 - idx2) == 1:  # Смежные узлы в пути
                                edge_in_paths.append(path_idx)

                    if edge_in_paths:
                        if len(edge_in_paths) == 1:
                            # Если ребро входит только в один путь
                            path_idx = edge_in_paths[0]
                            color_idx = path_idx % len(path_colors)
                            edge_color = path_colors[color_idx]
                        else:
                            # Если ребро входит в несколько путей, делаем его пурпурным
                            edge_color = "purple"
                        edge_width = "2.0"

                    edge = pydot.Edge(
                        str(i), str(child), dir="none",
                        color=edge_color, penwidth=edge_width,
                    )
                    graph.add_edge(edge)

    graph.write_png(output_png)
    return output_png