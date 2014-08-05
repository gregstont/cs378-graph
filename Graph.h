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
        {
            assert(ed >= 0);
        }
        
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
        {
            assert(ed >= 0);
        }
        
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
        {
            assert(ed >= 0);
        }
        
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

        typedef std::size_t vertex_descriptor;  // fix!
        typedef std::size_t edge_descriptor;    // fix!

        typedef vert_iter vertex_iterator;    // fix!
        typedef edge_iter edge_iterator;      // fix!
        typedef adj_iter adjacency_iterator; // fix!

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;
    
        struct edge {
            std::size_t edge_no;
            vertex_descriptor source;
            vertex_descriptor target;
        };


    public:
        // --------
        // add_edge
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor vdS, vertex_descriptor vdT, Graph& graph) {
            assert(vdS >= 0);
            assert(vdT >= 0);
            
            bool found = false;
            edge_descriptor ret = 0;
            
            for(std::vector<edge>::iterator it = graph._g[vdS].begin(); it != graph._g[vdS].end(); ++it) {
                if((*it).target == vdT) {
                    found = true;
                    break;
                }
            }

            if(!found) {
                ret = graph.edge_label++;
                struct edge new_edge = {ret, vdS, vdT};
                graph._g[vdS].push_back(new_edge);
                graph.edge_list.push_back(new_edge);
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
            graph._g.push_back( std::vector<edge>() );
            return graph.vertex_label++;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor vd, const Graph& graph) {
            assert(vd >= 0);
            return std::make_pair(adj_iter(&graph, 0, vd), adj_iter(&graph, graph._g[vd].size(), vd));
        }

        // ----
        // edge
        // ----

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor vdS, vertex_descriptor vdT, const Graph& graph) {
            assert(vdS >= 0);
            assert(vdT >= 0);
            edge_descriptor ed = 0;
            bool            b  = false;
            
            for(std::vector<edge>::const_iterator it = graph._g[vdS].begin(); it != graph._g[vdS].end(); ++it) {
                if((*it).target == vdT) {
                    ed = (*it).edge_no;
                    b = true;
                    break;
                }
            }
            
            return std::make_pair(ed, b);
        }

        // -----
        // edges
        // -----

        /**
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& graph) {
            return std::make_pair(edge_iter(&graph, 0), edge_iter(&graph, graph.edge_label));
        }

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph& graph) {
            return graph.edge_label;
        }

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph& graph) {
            return graph.vertex_label;
        }

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph& graph) {
            assert(ed >= 0);
            return graph.edge_list[ed].source;
        }

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph& graph) {
            assert(ed >= 0);
            return graph.edge_list[ed].target;
        }

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type num, const Graph& graph) {
            assert(num >= 0);
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
        std::vector< std::vector<Graph::edge> > _g;     //the 2d structure
        vertex_descriptor vertex_label;                 //counter for vertex labels
        edge_descriptor edge_label;                     //counter for edge labels
        std::deque<edge> edge_list;                     //could get rid of this...

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            return vertex_label >= 0 && edge_label >= 0;
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () {
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
