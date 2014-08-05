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
    
    /**
     * vertex iterator 
     * will iterate over every vertex in the graph
     */
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
        
        /**
         * creates a new vertex iterator
         * @param   *owner the graph from which this iterator represents
         * @param   ed the index of this iterator
         */
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
        
        /**
         * (pre)increment this iterator
         * @returns this with its new value
         */
        vert_iter& operator ++ () {
            ++index;
            return *this;
        }
    };
    
    /**
     * edge iterator
     * will iterate over every edge in the graph
     */
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
        
        /**
         * creates a new edge iterator
         * @param   *owner the graph from which this iterator represents
         * @param   ed the index of this iterator
         */
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
        
        /**
         * (pre)increment this iterator
         * @returns this with its new value
         */
        edge_iter& operator ++ () {
            ++index;
            return *this;
        }
    };
    
    /**
     * adjacent vertece iterator
     * will iterate over every vertex in the graph that has an edge from given vertex
     */
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
        
        /**
         * creates a new adjcent vertex iterator
         * @param   *owner the graph from which this iterator represents
         * @param   ed the index of this iterator
         * @param   vert the vertex of which to look at
         */
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
        
        /**
         * (pre)increment this iterator
         * @returns this with its new value
         */
        adj_iter& operator ++ () {
            ++index;
            return *this;
        }
    };
    
    public:
        // --------
        // typedefs
        // --------

        typedef std::size_t vertex_descriptor;
        typedef std::size_t edge_descriptor; //should make this struct edge, then could get rid of edge list

        typedef vert_iter vertex_iterator;
        typedef edge_iter edge_iterator;
        typedef adj_iter adjacency_iterator;

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
         * Adds edge (vdS,vdT) to the graph and returns the edge descriptor for the new edge
         * @param vdS   the vertex descriptor of the source
         * @param vdT   the vertex descriptor of the target
         * @param g     the graph to add the edge to
         * @returns     a pair with the edge descriptor and a boolean indicating whether or
         *              not an edge was added
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor vdS, vertex_descriptor vdT, Graph& g) {
            assert(vdS >= 0);
            assert(vdT >= 0);
            
            bool found = false;
            edge_descriptor ret = 0;
            
            for(std::vector<edge>::iterator it = g._g[vdS].begin(); it != g._g[vdS].end(); ++it) {
                if((*it).target == vdT) {
                    found = true;
                    break;
                }
            }

            if(!found) {
                ret = g.edge_label++;
                struct edge new_edge = {ret, vdS, vdT};
                g._g[vdS].push_back(new_edge);
                g.edge_list.push_back(new_edge);
            }
            
            return std::make_pair(ret, !found);
        }

        // ----------
        // add_vertex
        // ----------

        /**
         * Adds a vertex to the graph and returns the vertex descriptor for the new vertex.
         * @param g         the graph to add a vertex to
         * @returns         the vertex_descriptor of the added vertex
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            g._g.push_back( std::vector<edge>() );
            return g.vertex_label++;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * Returns an iterator-range providing access to the vertices adjacent to vertex 
         * u in graph g. For example, if u -> v is an edge in the graph, then v will be 
         * in this iterator-range.
         * @param   vd      the vertex to look at
         * @param   g       the graph to look in
         * @returns         a pair of iterators, begin and end
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor vd, const Graph& g) {
            assert(vd >= 0);
            return std::make_pair(adj_iter(&g, 0, vd), adj_iter(&g, g._g[vd].size(), vd));
        }

        // ----
        // edge
        // ----

        /**
         * If an edge from vertex u to vertex v exists, return a pair containing one such
         * edge and true. If there are no edges between u and v, return a pair with an 
         * arbitrary edge descriptor and false.
         * @param   vdS     vertex descriptor of the source
         * @param   vdT     vertex descriptor of the target
         * @param   g       the graph to look in
         * @returns         a pair including the edge descriptor of the found edge and a 
         *                  boolean indicating whether or not an edge was found
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor vdS, vertex_descriptor vdT, const Graph& g) {
            assert(vdS >= 0);
            assert(vdT >= 0);
            edge_descriptor ed = 0;
            bool            b  = false;
            
            for(std::vector<edge>::const_iterator it = g._g[vdS].begin(); it != g._g[vdS].end(); ++it) {
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
         * Returns an iterator-range providing access to the edge set of graph g.
         * @param   g   the graph to look in
         * @returns     a pair of iterators, begin and end encompassing all edges
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            return std::make_pair(edge_iter(&g, 0), edge_iter(&g, g.edge_label));
        }

        // ---------
        // num_edges
        // ---------

        /**
         * Returns the number of edges in the graph g.
         * @param   g   the graph in question
         * @returns     the number of edges in graph g
         */
        friend edges_size_type num_edges (const Graph& g) {
            return g.edge_label;
        }

        // ------------
        // num_vertices
        // ------------

        /**
         * Returns the number of vertices in the graph g.
         * @param   g   the graph in question
         * @returns     the number of vertices in graph g
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            return g.vertex_label;
        }

        // ------
        // source
        // ------

        /**
         * Returns the source vertex of edge ed.
         * @param   ed  the edge descriptor of the edge in question
         * @param   g   the graph to look in
         * @returns     the vertex descriptor of the source of the edge
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph& g) {
            assert(ed >= 0);
            return g.edge_list[ed].source;
        }

        // ------
        // target
        // ------

        /**
         * Returns the target vertex of edge ed.
         * @param   ed  the edge descriptor of the edge in question
         * @param   g   the graph to look in
         * @returns     the vertex descriptor of the target of the edge
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph& g) {
            assert(ed >= 0);
            return g.edge_list[ed].target;
        }

        // ------
        // vertex
        // ------

        /**
         * Returns the nth vertex in the graph's vertex list.
         * @param   n   the index of the vertex to return
         * @param   g   the graph to look in
         * @returns     the vertex descriptor of the nth vertex
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& g) {
            assert(n >= 0);
            return n;
        }

        // --------
        // vertices
        // --------

        /**
         * Returns an iterator-range providing access to the vertex set of graph g.
         * @param   g   the graph to look at
         * @returns     a pair of iterators which encompass all vertices in g
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            return std::make_pair(vert_iter(&g,0), vert_iter(&g, g.vertex_label));
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
         * private function to test validity of a constructed graph
         * @returns     true if valid
         */
        bool valid () const {
            return vertex_label >= 0 && edge_label >= 0;
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         * A simple graph implementation based on boost's adjacency_list.
         * Constructs a new graph with no edges or vertices
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
