#include"contactcount.h"
    void ContactCount::BeginContact(b2Contact *contact)
    {
        float m1=contact->GetFixtureA()->GetBody()->GetMass();
        float m2=contact->GetFixtureB()->GetBody()->GetMass();
        b2Vec2 v1=contact->GetFixtureA()->GetBody()->GetLinearVelocity();
        b2Vec2 v2=contact->GetFixtureB()->GetBody()->GetLinearVelocity();
        /*Rectangle* w1=(Rectangle*)contact->GetFixtureA()->GetBody()->(GetUserData());
        Rectangle* w2=(Rectangle*)contact->GetFixtureB()->GetBody()->(GetUserData());*/
                 std::cout << "colli !" << std::endl ;
    }
