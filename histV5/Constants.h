#ifndef Constants_h
#define Constants_h

class Constants {
public:
    Constants(); //constructor
    ~Constants(); //destructor
    
    float Pion() const;
    float Proton() const;
    float K0() const;
    float L0() const;
    float Light() const;
private:
    const float massPion;   // GeV/c^2
    const float massProton;  // GeV/c^2
    const float massK0;    // GeV/c^2
    const float massLambda0;  // GeV/c^2
    const float lightVelocity; // cm/ps
};

#endif /* Constants_h */
