#ifndef QUADTREE_H

#include <memory>
#include <vector>


struct pt2d
{
    float x = 0.0;
    float y = 0.0;

    // constructor
    pt2d(float _cx, float _cy)
    {
        x = _cx;
        y = _cy;
    }
    pt2d(){
        x = .0;
        y = .0;
    }
};


struct BoundaryBox
{
    float cx;	// center of the node (x-coordinate)
    float cy;	// center of the node (y-coordinate)
    float dim;	// width of the node

    // constructor
    BoundaryBox(float _cx, float _cy, float _dim)
    {
        cx  = _cx;
        cy  = _cy;
        dim = _dim;
    }
};


class Quadtree
{
public:
    // Children nodes
    Quadtree *northWest;
    Quadtree *northEast;
    Quadtree *southWest;
    Quadtree *southEast;

    // dimensions of the node
    std::shared_ptr<BoundaryBox> boundary2;

    // elements in this node
    std::vector<pt2d> children;

    // minimum amount of pts to split the node
    unsigned int maxAmtElements = 1;

    // maximum depth of the children nodes
    int maxDepth = 6;

    int nodeDepth;

    Quadtree* parent;

    // auxiliary function used by delete_element()
    void concatenate_nodes(Quadtree *concat_this_node_maybe);

    // auxiliary function used by delete_element()
    Quadtree* fetch_node(pt2d seekPt);

    [[maybe_unused]] void removeChildren();

    void clearNode();

    void clear(Quadtree *t);

public:
    // constructor
    Quadtree(std::shared_ptr<BoundaryBox> BB_init, Quadtree *parent, int _nodeDepth);
    
    //destructor
    ~Quadtree();

    bool insert(pt2d insertPt);

    // create four children that fully divide this quad into four quads of equal area
    void subdivide();

    
#ifdef GENGINE_H
    void traverse_and_draw(game_engine *Engine);
    void _traverse_and_draw(game_engine *Engine, Quadtree *subtree);
#endif

    int count_nodes(Quadtree *t);

    int count_elements(Quadtree *t);

    // returns all points corresponding to the node in which this point (seekPt) resides
    [[maybe_unused]] std::vector<pt2d> fetch_points(pt2d seekPt);

    bool delete_element(pt2d deletePt);

    // relocate a single element of the tree
    [[maybe_unused]] bool relocate_element(pt2d ptOrigin, pt2d PtMoveTo);
};


#define QUADTREE_H
#endif