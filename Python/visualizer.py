import pydot


def draw_tree(nodes, path, output_png="./Images/tree.png"):
    """
    Создаёт изображение n-арного дерева с выделенным найденный путём

    :param nodes: - список узлов дерева
    :param path: - путь для сохранения изображения
    :param output_png: - список значений узлов, составляющих найденный путь с нечётными значениями
    :return: путь к сохранённому изображению
    """
    # Граф n-арного дерева
    graph = pydot.Dot(graph_type="graph", rankdir="TR")

    # Словарь для сопоставления узлов по их номерам
    if path: value_to_index = {node["number"] : i for i, node in enumerate(nodes) if node is not None}

    # Добавляем узлы в граф
    for i, node in enumerate(nodes):
        if node is not None:
            node_value = node["number"]
            fillcolor = "lightblue"

            if path and node_value in path: fillcolor = "lightgreen"

            graph_node = pydot.Node(
                str(i), label=str(node_value), shape="circle",
                style="filled", fillcolor=fillcolor,
            )
            graph.add_node(graph_node)

            # Добавляем рёбра в граф
            for j in range(node["arity"]):
                child = node[f"child{j}"]

                if child is not None:
                    edge_color = "black"
                    edge_width = "1.0"

                    if path and node["number"] in path and nodes[child] is not None:
                        child_value = nodes[child]["number"]
                        if child_value in path:
                            path_idx1 = path.index(node["number"])
                            path_idx2 = path.index(child_value)
                            if abs(path_idx1 - path_idx2) == 1:
                                edge_color = "green"
                                edge_width = "2.0"

                    edge = pydot.Edge(
                        str(i), str(child), dir="none",
                        color=edge_color, penwidth=edge_width,
                    )
                    graph.add_edge(edge)

    graph.write_png(output_png)
    return output_png