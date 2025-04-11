import pydot


def draw_tree(nodes, output_png="./Images/tree.png"):
    graph = pydot.Dot(graph_type="graph", rankdir="TR")

    for i, node in enumerate(nodes):
        if node is not None:
            graph_node = pydot.Node(str(i), label=str(node["number"]),
                                    shape="circle", style="filled",
                                    fillcolor="lightblue")

            graph.add_node(graph_node)

            for j in range(node["arity"]):
                if node[f"child{j}"] is not None:
                    edge = pydot.Edge(str(i), str(node[f"child{j}"]), dir="none")
                    graph.add_edge(edge)

    graph.write_png(output_png)
    return output_png