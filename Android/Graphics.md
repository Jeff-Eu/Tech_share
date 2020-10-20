# Graphics in Android

## Trigonometric functions in Java
* `acos(double a)` returns an angle between 0.0 and pi.
* `asin(double a)` returns an angle between -pi/2 and pi/2
* `atan(double a)` returns an angle between -pi/2 and pi/2


## Matrix
* Transformation matrix
```
[ sx*cosΘ  −sx*sinΘ  tx
  sy*sinΘ   sy*cosΘ  ty
    0        0        1 ]
```

* Get Scale (Assume that the scale value is larger than zero)
```java
	// https://math.stackexchange.com/questions/13150/extracting-rotation-scale-values-from-2d-transformation-matrix/13165
	// https://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati
	/* todo: Here sx, sy are both larger than 0.
	 * In the future we need to take negative values of sx, sy into consideration.
	 */
	public static float[] getScaleVector(Matrix matrix) {
		float sx, sy;
		float[] f = new float[9];
		matrix.getValues(f);
		sx = (float) Math.hypot(f[0], f[1]);
		sy = (float) Math.hypot(f[3], f[4]);

		// https://stackoverflow.com/questions/3160347/java-how-initialize-an-array-in-java-in-one-line
		return new float[]{sx, sy};
	}
```

* Get Rotation
```java
	//	[ sx*cosΘ  −sx*sinΘ  tx        [ 0a  1b  2c
	//    sy*sinΘ   sy*cosΘ  ty    ==    3d  4e  5f
	//     0         0        1 ]        6g  7h  8i ]
	//
	//	 Premise: The scale value must be >= zero
	public static double getRotationDegree(Matrix matrix) {

		final double TO_DEGREE = 180 / Math.PI;
		float[] f = new float[9];
		matrix.getValues(f);

		// atan() is between pi/2 and -pi/2
		double radian;

		if (f[4] != 0)
			// tanΘ == -b/a == d/e
			radian = Math.atan(f[3] / f[4]);
		else // Θ is pi/2 or -pi/2
			if (f[3] > 0)
				return 90;
			else
				return -90;

		if (f[3] == 0)
			if (f[0] > 0)
				return 0;
			else
				return 180;
		/*
		 * Please see tan() diagram
		 * e.g. https://www.analyzemath.com/Inverse-Trigonometric-Functions/Arctan.html
		 * */
		if (radian > 0) { // quadrant I, III
			if (f[0] > 0) // I
				return radian * TO_DEGREE;
			else // quadrant III
				return radian * TO_DEGREE - Math.PI;
		} else { // radian < 0. quadrant II, IV
			if (f[0] > 0) // IV
				return radian * TO_DEGREE;
			else // II
				return radian * TO_DEGREE + Math.PI;
		}
	}
```

* Rotation unit is `degree` instead of `radian`. There are two types of transformation matrix, preXXX and postXXX. E.g.,
	```java
	// Postconcats the matrix with the specified rotation. M' = R(degrees, px, py) * M
	// The Matrix is at the "post" position of the Rotation, so it's R * M = M'
	Matrix.postRotate(float degrees, float px, float py)

	// Preconcats the matrix with the specified rotation. M' = M * R(degrees)
	// The Matrix is at the "pre" position of the Rotation, so it's M * R = M'
	Matrix.preRotate(float degrees, float px, float py)
	```

* [It's `Row major`](https://stackoverflow.com/questions/32190006/android-matrix-setvalues-row-major-or-column-major)

	* Matrix's elements are ordered by rows, from left to right.
	E.g., the function below from mvb. Notice the order of the `f` array.
		```java
			// https://math.stackexchange.com/questions/13150/extracting-rotation-scale-values-from-2d-transformation-matrix/13165
			// https://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati
			/* todo: Here sx, sy are both larger than 0.
			* In the future we need to take negative values of sx, sy into consideration.
			*/
			public static float[] getScaleVector(Matrix matrix) {
				float sx, sy;
				float[] f = new float[9];
				matrix.getValues(f);
				sx = (float) Math.hypot(f[0], f[1]);
				sy = (float) Math.hypot(f[3], f[4]);

				// https://stackoverflow.com/questions/3160347/java-how-initialize-an-array-in-java-in-one-line
				return new float[]{sx, sy};
			}
		```


