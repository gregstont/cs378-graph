// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector
#include <deque>
// -----
// Graph
// -----

class Graph {
    public:
    
    class vert_iter {
        
    private:
        std::size_t index;
        const Graph *owner;
        
    public:
        /**
         * checks to see if the lhs == rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  true if the lhs and rhs point to the same value
         */
        friend bool operator == (const vert_iter& lhs, const vert_iter& rhs) {
            return (lhs.owner == rhs.owner) && (lhs.index == rhs.index);;
        }
        
        /**
         * checks to see if the lhs != rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  false if the lhs and rhs point to the same value
         */
        friend bool operator != (const vert_iter& lhs, const vert_iter& rhs) {
            return !(lhs == rhs);
        }
        
        vert_iter(const Graph *owner_, std::size_t ed) :
        index(ed),
        owner(owner_)
        {}
        
        /**
         * dereference this iterator
         * @returns the value at which this iterator is pointing
         */
        int operator * () const {
            return index;
        }
        
        vert_iter& operator ++ () {
            ++index;
            return *this;
        }
    };
    
    
    class edge_iter {
        
    private:
        std::size_t index;
        const Graph *owner;
        
    public:
        /**
         * checks to see if the lhs == rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  true if the lhs and rhs point to the same value
         */
        friend bool operator == (const edge_iter& lhs, const edge_iter& rhs) {
            return (lhs.owner == rhs.owner) && (lhs.index == rhs.index);;
        }
        
        /**
         * checks to see if the lhs != rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  false if the lhs and rhs point to the same value
         */
        friend bool operator != (const edge_iter& lhs, const edge_iter& rhs) {
            return !(lhs == rhs);
        }
        
        
        
        edge_iter(const Graph *owner_, std::size_t ed) :
            index(ed),
            owner(owner_)
        {}
        
        /**
         * dereference this iterator
         * @returns the value at which this iterator is pointing
         */
        int operator * () const {
            return owner->edge_list[index].edge_no;
        }
        
        edge_iter& operator ++ () {
            ++index;
            return *this;
        }
    };
    
    class adj_iter {
        
    private:
        int vertex;
        std::size_t index;
        const Graph *owner;
        
    public:
        /**
         * checks to see if the lhs == rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  true if the lhs and rhs point to the same value
         */
        friend bool operator == (const adj_iter& lhs, const adj_iter& rhs) {
            return (lhs.owner == rhs.owner) && (lhs.index == rhs.index) && (lhs.vertex == rhs.vertex);
        }
        
        /**
         * checks to see if the lhs != rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  false if the lhs and rhs point to the same value
         */
        friend bool operator != (const adj_iter& lhs, const adj_iter& rhs) {
            return !(lhs == rhs);
        }
        
        adj_iter(const Graph *owner_, std::size_t ed, int vert) :
            vertex(vert),
            index(ed),
            owner(owner_)
        {}
        
        /**
         * dereference this iterator
         * @returns the value at which this iterator is pointing
         */
        int operator * () const {
            return owner->_g[vertex][index].target;
        }
        
        adj_iter& operator ++ () {
            ++index;
            return *this;
        }
    };
    
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;  // fix!
    
        struct edge {
            std::size_t edge_no;
            vertex_descriptor source;
            vertex_descriptor target;
            //vertex_descriptor vd;
            //edge_descriptor ed;
        };
        typedef int edge_descriptor;    // fix!

        typedef vert_iter vertex_iterator;    // fix!
        typedef edge_iter edge_iterator;      // fix!
        typedef adj_iter adjacency_iterator; // fix!

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;
    


    public:
        // --------
        // add_edge
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor vdS, vertex_descriptor vdT, Graph& graph) {
            // <your code>
            using namespace std;
            //edge_descriptor ed = 0;
            //bool            b  = false;
            bool found = false;
            edge_descriptor ret = 0;
            //cout << "Sdfssadsaddf 0" << endl;
        
            
            
            for(std::vector<edge>::iterator it = graph._g[vdS].begin(); it != graph._g[vdS].end(); ++it) {
                //cout << "Sdfsdf 0" << endl;
                if((*it).target == vdT) {
                    found = true;
                    break;
                }
            }
            

            if(!found) {
                ret = graph.edge_label;
                struct edge new_edge;
                new_edge.target = vdT;
                new_edge.source = vdS;
                new_edge.edge_no = ret;
                graph._g[vdS].push_back(new_edge);
                graph.edge_list.push_back(new_edge);
                ++graph.edge_label;
            }
            
            
            return std::make_pair(ret, !found);
        }

        // ----------
        // add_vertex
        // ----------

        /**
         * <your documentation>
         */
        friend vertex_descriptor add_vertex (Graph& graph) {
            // <your code>
            using namespace std;

            graph._g.push_back( std::vector<edge>() );
            vertex_descriptor temp = graph.vertex_label;
            ++graph.vertex_label;
            return temp;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor vd, const Graph& graph) {
            // <your code>
            /*static int a [] = {0, 0};     // dummy data
            adjacency_iterator b = a;
            adjacency_iterator e = a + 2;*/
            return std::make_pair(adj_iter(&graph, 0, vd), adj_iter(&graph, graph._g[vd].size(), vd));
        }

        // ----
        // edge
        // ----

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor vdS, vertex_descriptor vdT, const Graph& graph) {
            // <your code>
            edge_descriptor ed = 0;
            bool            b  = false;
            
            
            for(std::vector<edge>::const_iterator it = graph._g[vdS].begin(); it != graph._g[vdS].end(); ++it) {
                //cout << "Sdfsdf 0" << endl;
                if((*it).target == vdT) {
                    ed = (*it).edge_no;
                    b = true;
                    break;
                }
            }
            
            /*
            bool success = false;
            edge_descriptor ret = 0;
            if(find(graph._g[vdS].begin(), graph._g[vdS].end(), vdT) == graph._g[vdS].end()) {
                success = true;
                ret = graph.edge_label++;
                graph._g[vdS].push_back(vdT);
            }*/
            
            return std::make_pair(ed, b);
        }

        // -----
        // edges
        // -----

        /**
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& graph) {
            // <your code>
            /*static int a [] = {0, 0};     // dummy data
            edge_iterator b = a;
            edge_iterator e = a + 2;*/
            return std::make_pair(edge_iter(&graph, (std::size_t)0), edge_iter(&graph, (std::size_t)graph.edge_label));
        }

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph& graph) {
            // <your code>
            //edges_size_type s = 1; // fix
            return graph.edge_label;
        }

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph& graph) {
            // <your code>
            //vertices_size_type s = 1; // fix
            return graph.vertex_label;
        }

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph& graph) {
            // <your code>
            using namespace std;
            //vertex_descriptor v = 0; // fix
            return graph.edge_list[ed].source;
            //return v;
        }

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph& graph) {
            // <your code>
            //vertex_descriptor v = 0; // fix
            return graph.edge_list[ed].target;
        }

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type num, const Graph& graph) {
            // <your code>
            //vertex_descriptor vd = 0; // fix
            //return vd;
            return num;
        }

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& graph) {
            return std::make_pair(vert_iter(&graph,0), vert_iter(&graph, graph.vertex_label));
        }

    private:
        // ----
        // data
        // ----
        std::vector< std::vector<Graph::edge> > _g; // something like this
        vertex_descriptor vertex_label;
        edge_descriptor edge_label;
        std::deque<edge> edge_list;

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () {
            // <your code>
            vertex_label = 0;
            edge_label = 0;
            assert(valid());
        }

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
