#include <tuple>
#include <algorithm>
#include <vector>

using namespace std;

class AssignedNode {
    private:
        Node _node;
        float _bestTime;
        vector<tuple<Node, float>> _candidates;

    public:
        AssignedNode(){};
        AssignedNode(Node node, float bestTime, vector<tuple<Node, float>> nodes){
            _node = node;
            _bestTime = bestTime;
            for (tuple<Node, float> node : nodes){
                _candidates.push_back(node);
            }
        }

        void SetNode(Node node){ _node = node; };
        void SetBestTime(float bestTime){ _bestTime = bestTime; };
        void SetCandidates(vector<tuple<Node, float>> candidates){
            _candidates.clear();
            for (tuple<Node, float> candidate : candidates){
                _candidates.push_back(candidate);
            }
            //cout << "SetCandidates: " << _candidates.size() << endl;
        };
        void AddCandidate(tuple <Node, float> candidate){ _candidates.push_back(candidate); };
        void RemoveFromCandidate(Node node){
            int nodeNumber = node.GetNumber();

            auto it = find_if(_candidates.begin(),
                                _candidates.end(),
                                [nodeNumber](tuple<Node, float>& obj) {
                                    return (get<0>(obj).GetNumber() == nodeNumber);
                                });

            if (it != _candidates.end()){
              auto index = distance(_candidates.begin(), it);
              //PrintCandidates();
              //cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Eliminè de " << index << endl;
              _candidates.erase(_candidates.begin() + index);
              //PrintCandidates();
            }
        };

        void PrintCandidates(){
            cout << "Candidates node (" << _node.GetNumber() << "): " << endl;
            if (_candidates.size() != 0){
                for (tuple<Node, float> candidate : _candidates){
                    cout << "" << get<0>(candidate).GetNumber();
                }
                cout << endl;
                cout << "Best candidate: " << endl;
                cout << "Node: " << get<0>(GetBestCandidate()).GetNumber() << " Time: " << get<1>(GetBestCandidate()) << endl;
            } else {
                cout << "No Candidates" << endl;
            }

        };

        void PrintCandidatesLine(){
            cout << "Candidates node (" << _node.GetNumber() << "): " << endl;
            if (_candidates.size() != 0){
                for (tuple<Node, float> candidate : _candidates){
                    cout << "" << get<0>(candidate).GetNumber();
                }
                cout << endl;
                cout << "Best candidate: ";
                cout << "Node: " << get<0>(GetBestCandidate()).GetNumber() << " Time: " << get<1>(GetBestCandidate()) << endl;
            } else {
                cout << "No Candidates" << endl;
            }

        };

        tuple<Node, float> GetBestCandidate(){
            tuple<Node, float> bestCandidate = _candidates.at(0);
            for (tuple<Node, float> candidate : _candidates){
                if (get<1>(candidate) < get<1>(bestCandidate)){
                    bestCandidate = candidate;
                }
            }
            //RemoveFromCandidate(get<0>(bestCandidate));
            return bestCandidate;
        }

        Node GetNode( ) { return _node; };
        float GetBestTime( ) { return _bestTime; };
        vector<tuple<Node, float>> GetCandidates( ) { return _candidates; };
        vector<Node> GetCandidatesNodes( ) {
            vector<Node> nodesCandidates;
            for (tuple<Node, float> nodeCandidate : _candidates){
                nodesCandidates.push_back(get<0>(nodeCandidate));
            }
            return nodesCandidates;
        };

};
