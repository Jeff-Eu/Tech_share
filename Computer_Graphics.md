* Bézier curve
	* Math background
		* https://javascript.info/bezier-curve
        * [Opt] https://www.youtube.com/watch?v=2HvH9cmHbG4
		
	* Quadratic Bézier Curve
		* Js Introduction (the params on Js are the same with Android)
			* https://www.w3schools.com/tags/canvas_quadraticcurveto.asp
		* Demo
			* http://blogs.sitepointstatic.com/examples/tech/canvas-curves/quadratic-curve.html

	* Cubic Bézier Curve
		* Js Introduction (the params on Js are the same with Android)
			* https://www.w3schools.com/tags/canvas_beziercurveto.asp
		* Demo
			* http://www.victoriakirst.com/beziertool/
			* http://blogs.sitepointstatic.com/examples/tech/canvas-curves/bezier-curve.html
		* Restricting some conditions for more beautiful curve
			* https://github.com/PaoloConte/smooth-line-chart/blob/master/SmoothChartSample/src/org/paoloconte/smoothchart/SmoothLineChart.java

	* [Implement] Android
		* Implement curve through points
			* Smooth line chart
				* https://github.com/PaoloConte/smooth-line-chart
				* https://github.com/PaoloConte/smooth-line-chart/blob/master/SmoothChartSample/src/org/paoloconte/smoothchart/SmoothLineChart.java

		* Freehand - Vector drawing app
			* https://github.com/CalHinshaw/Freehand

* [2D collision detection](https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection)
	* AABB ( Axis-Aligned Bounding Box )
	
	Only 4 checks needed. Quite fast !!
	
	```java
	/**
     * Returns true iff the two specified rectangles intersect. In no event are
     * either of the rectangles modified. To record the intersection,
     * use intersect() or setIntersect().
     *
     * @param a The first rectangle being tested for intersection
     * @param b The second rectangle being tested for intersection
     * @return true iff the two specified rectangles intersect. In no event are
     *              either of the rectangles modified.
     */
    public static boolean intersects(RectF a, RectF b) {
        return a.left < b.right && b.left < a.right
                && a.top < b.bottom && b.top < a.bottom;
    }
	```
	* [SAT](http://www.dyn4j.org/2010/01/sat/)