//
//  PaintStroke.cpp
//  cinder02
//
//  Created by Michael Oneppo on 3/7/15.
//
//

#include "PaintStroke.h"

using namespace ci;
using namespace std;

vector<vec2> Interpolate(vector<vec2> segmentPoints, float scale)
{
    auto controlPoints = vector<vec2>();
    
    if (segmentPoints.size() < 2) return controlPoints;
    
    for (int i = 0; i < segmentPoints.size(); i++)
    {
        if (i == 0)
        {
            vec2 p1 = segmentPoints[i];
            vec2 p2 = segmentPoints[i + 1];
            
            vec2 tangent = (p2 - p1);
            vec2 q1 = p1 + scale * tangent;
            
            controlPoints.push_back(p1);
            controlPoints.push_back(q1);
        }
        else if (i == segmentPoints.size() - 1)
        {
            vec2 p0 = segmentPoints[i - 1];
            vec2 p1 = segmentPoints[i];
            vec2 tangent = (p1 - p0);
            vec2 q0 = p1 - scale * tangent;
            
            controlPoints.push_back(q0);
            controlPoints.push_back(p1);
        }
        else
        {
            vec2 p0 = segmentPoints[i - 1];
            vec2 p1 = segmentPoints[i];
            vec2 p2 = segmentPoints[i + 1];
            
            vec2 tangent = normalize(p2 - p0);
            vec2 q0 = p1 - scale * tangent * length(p1 - p0);
            vec2 q1 = p1 + scale * tangent * length(p2 - p1);
            
            controlPoints.push_back(q0);
            controlPoints.push_back(p1);
            controlPoints.push_back(q1);
        }
    }
    
    return controlPoints;
}


vector<vec2> Simplify(vector<vec2> sourcePoints, float minSqrDistance, float maxSqrDistance, float scale)
{
    vector<vec2> samplePoints = vector<vec2>();
    
    if(sourcePoints.size() < 2) return samplePoints;
    
    samplePoints.push_back(sourcePoints[0]);
    
    vec2 potentialSamplePoint = sourcePoints[1];
    
    for (int i = 2; i < sourcePoints.size(); i++ )
    {
        if((length2(potentialSamplePoint - sourcePoints[i]) > minSqrDistance) &&
           (length2(samplePoints.back()  - sourcePoints[i]) > maxSqrDistance))
        {
            samplePoints.push_back(potentialSamplePoint);
        }
        
        potentialSamplePoint = sourcePoints[i];
    }
    
    vec2 p1 = samplePoints.back();
    samplePoints.pop_back();
    vec2 p0 = samplePoints.back();
    vec2 tangent = normalize(p0 - potentialSamplePoint);
    float d2 = length(potentialSamplePoint - p1);
    float d1 = length(p1 - p0);
    p1 = p1 + tangent * ((d1 - d2) / 2.0f);
    
    samplePoints.push_back(p1);
    samplePoints.push_back(potentialSamplePoint);
    
    return Interpolate(samplePoints, scale);
}

void drawPath(const vector<vec2>& points) {
    auto angles = deque<float>();
    auto radii = deque<float>();
    angles.push_front(0);
    radii.push_front(0);
    
    for (int c = points.size() - 1; c > 0; c-- )
    {
        vec2 p = points[c];
        vec2 nb = points[c+1];
        
        vec2 d = p - nb;
        angles.push_front(atan2(d.y, d.x));
        radii.push_front(CLAMP(10.0f - length(d)/3.0f, 2.0f, 10.0f));
    }
    
    for ( int c = points.size() - 4; c > 0; c-- )
    {
        vec2 p = points[c];
        vec2 nb = points[c+1];
        vec2 nbB = points[c-1];
        
        vec2 point_a = vec2(nbB.x + radii[c-1] * cos(angles[c-1] + M_PI * .5),
                            nbB.y + radii[c-1] * sin(angles[c-1] + M_PI * .5));
        vec2 point_b = vec2(nbB.x - radii[c-1] * cos(angles[c-1] + M_PI * .5),
                            nbB.y - radii[c-1] * sin(angles[c-1] + M_PI * .5));
        
        vec2 point_c = vec2(p.x + radii[c] * cos(angles[c] + M_PI * .5),
                            p.y + radii[c] * sin(angles[c] + M_PI * .5));
        vec2 point_d = vec2(p.x - radii[c] * cos(angles[c] + M_PI * .5),
                            p.y - radii[c] * sin(angles[c] + M_PI * .5));
        
        vec2 point_e = vec2(nb.x + radii[c+1] * cos(angles[c+1] + M_PI * .5),
                            nb.y + radii[c+1] * sin(angles[c+1] + M_PI * .5));
        vec2 point_f = vec2(nb.x - radii[c+1] * cos(angles[c+1] + M_PI * .5),
                            nb.y - radii[c+1] * sin(angles[c+1] + M_PI * .5));
        
        vec2 point_ac = point_a + (point_c - point_a) * 0.5f;
        vec2 point_ce = point_c + (point_e - point_c) * 0.5f;
        
        vec2 point_bd = point_b + (point_d - point_b) * 0.5f;
        vec2 point_df = point_d + (point_f - point_d) * 0.5f;
        
        Shape2d s;
        s.moveTo(point_bd);
        s.quadTo(point_d, point_df);
        
        s.lineTo(point_ce);
        s.quadTo(point_c, point_ac);
        
        s.close();
        
        gl::drawSolid(s);
        
    }
}


void PaintStroke::AddPoint(vec2 pt)
{
    mPoints.push_back(pt);
    mDirty = true;
}

void PaintStroke::Draw()
{
    gl::color(.8,.8,.8);
    drawPath(mPoints);
}