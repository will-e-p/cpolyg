#include "Quadrature.h"

using namespace arma;

mat Quadratures::lin2 = {{-0.5773502691896257, 1.0},
                         { 0.5773502691896257, 1.0}};
mat Quadratures::lin4 = {{-0.3399810435848563, 0.6521451548625461},
                         { 0.3399810435848563, 0.6521451548625461},
                         {-0.8611363115940526, 0.3478548451374538},
                         { 0.8611363115940526, 0.3478548451374538}};
mat Quadratures::lin6 = {{ 0.6612093864662645, 0.3607615730481386},
                         {-0.6612093864662645, 0.3607615730481386},
                         {-0.2386191860831969, 0.4679139345726910},
                         { 0.2386191860831969, 0.4679139345726910},
                         {-0.9324695142031521, 0.1713244923791704},
                         { 0.9324695142031521, 0.1713244923791704}};
mat Quadratures::lin10 = {{ 0.1488743389816312, 0.2955242247147529},
                          {-0.1488743389816312, 0.2955242247147529},
                          {-0.4333953941292472, 0.2692667193099963},
                          { 0.4333953941292472, 0.2692667193099963},
                          {-0.6794095682990244, 0.2190863625159820},
                          { 0.6794095682990244, 0.2190863625159820},
                          {-0.8650633666889845, 0.1494513491505806},
                          { 0.8650633666889845, 0.1494513491505806},
                          {-0.9739065285171717, 0.0666713443086881},
                          { 0.9739065285171717, 0.0666713443086881}};

mat Quadratures::tri2 = {{0.16666666666667, 0.16666666666667, 0.33333333333333},
                         {0.16666666666667, 0.66666666666667, 0.33333333333333},
                         {0.66666666666667, 0.16666666666667, 0.33333333333333}};
mat Quadratures::tri4 = {{0.44594849091597, 0.44594849091597, 0.22338158967801},
                         {0.44594849091597, 0.10810301816807, 0.22338158967801},
                         {0.10810301816807, 0.44594849091597, 0.22338158967801},
                         {0.09157621350977, 0.09157621350977, 0.10995174365532},
                         {0.09157621350977, 0.81684757298046, 0.10995174365532},
                         {0.81684757298046, 0.09157621350977, 0.10995174365532}};
mat Quadratures::tri6 = {{0.24928674517091, 0.24928674517091, 0.11678627572638},
                         {0.24928674517091, 0.50142650965818, 0.11678627572638},
                         {0.50142650965818, 0.24928674517091, 0.11678627572638},
                         {0.06308901449150, 0.06308901449150, 0.05084490637021},
                         {0.06308901449150, 0.87382197101700, 0.05084490637021},
                         {0.87382197101700, 0.06308901449150, 0.05084490637021},
                         {0.31035245103378, 0.63650249912140, 0.08285107561837},
                         {0.63650249912140, 0.05314504984482, 0.08285107561837},
                         {0.05314504984482, 0.31035245103378, 0.08285107561837},
                         {0.63650249912140, 0.31035245103378, 0.08285107561837},
                         {0.31035245103378, 0.05314504984482, 0.08285107561837},
                         {0.05314504984482, 0.63650249912140, 0.08285107561837}};
mat Quadratures::tri10 = {{0.33333333333333, 0.33333333333333, 0.09081799038275},
                          {0.48557763338366, 0.48557763338366, 0.03672595775647},
                          {0.48557763338366, 0.02884473323269, 0.03672595775647},
                          {0.02884473323269, 0.48557763338366, 0.03672595775647},
                          {0.10948157548504, 0.10948157548504, 0.04532105943553},
                          {0.10948157548504, 0.78103684902993, 0.04532105943553},
                          {0.78103684902993, 0.10948157548504, 0.04532105943553},
                          {0.30793983876412, 0.55035294182100, 0.07275791684542},
                          {0.55035294182100, 0.14170721941488, 0.07275791684542},
                          {0.14170721941488, 0.30793983876412, 0.07275791684542},
                          {0.55035294182100, 0.30793983876412, 0.07275791684542},
                          {0.30793983876412, 0.14170721941488, 0.07275791684542},
                          {0.14170721941488, 0.55035294182100, 0.07275791684542},
                          {0.24667256063990, 0.72832390459741, 0.02832724253106},
                          {0.72832390459741, 0.02500353476269, 0.02832724253106},
                          {0.02500353476269, 0.24667256063990, 0.02832724253106},
                          {0.72832390459741, 0.24667256063990, 0.02832724253106},
                          {0.24667256063990, 0.02500353476269, 0.02832724253106},
                          {0.02500353476269, 0.72832390459741, 0.02832724253106},
                          {0.06680325101220, 0.92365593358750, 0.00942166696373},
                          {0.92365593358750, 0.00954081540030, 0.00942166696373},
                          {0.00954081540030, 0.06680325101220, 0.00942166696373},
                          {0.92365593358750, 0.06680325101220, 0.00942166696373},
                          {0.06680325101220, 0.00954081540030, 0.00942166696373},
                          {0.00954081540030, 0.92365593358750, 0.00942166696373}};
