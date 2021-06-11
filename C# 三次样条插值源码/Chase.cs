using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MyAlgbra
{
    class Chasing
    {
        protected int N;//Dimension of Martrix Ax=d;
        protected double[] d;//Ax=d;
        protected double[] Aa;//a in A;
        protected double[] Ab; //b in A:
        protected double[] Ac;// c in A;
        protected double[] L;//LU-->L;
        protected double[] U;//LU-->U;
        public double[] S;//store the result;
        //constructor without parameters;
        public Chasing()
        {

        }
        public bool Init(double[] a, double[] b, double[] c, double[] d)
        {
            //check validation of dimentions;
            int na = a.Length;
            int nb = b.Length;
            int nc = c.Length;
            int nd = d.Length;

            if (nb < 3)
                return false;

            N = nb;

            if (na != N - 1 || nc != N - 1 || nd != N)
                return false;
            S = new double[N];
            L = new double[N - 1];
            U = new double[N];

            Aa = new double[N - 1];
            Ab = new double[N];
            Ac = new double[N - 1];
            this.d = new double[N];

            //init Aa,Ab,Ac,Ad;
            for (int i = 0; i <= N - 2; i++)
            {
                Ab[i] = b[i];
                this.d[i] = d[i];

                Aa[i] = a[i];
                Ac[i] = c[i];
            }

            Ab[N - 1] = b[N - 1];
            this.d[N - 1] = d[N - 1];
            return true;
        }
        public bool Solve(out double[] R)
        {
            R = new double[Ab.Length];          /*********************A=LU***********************************/
            U[0] = Ab[0];
            for (int i = 2; i <= N; i++)
            {
                // L[i] = Aa[i] / U[i - 1];
                L[i - 2] = Aa[i - 2] / U[i - 2];
                //U[i]=Ab[i]-Ac[i-1]*L[i];
                U[i - 1] = Ab[i - 1] - Ac[i - 2] * L[i - 2];
            }
            /*************************END of A=LU **********************/

            /****************       Ly=d   ******************************/
            double[] Y = new double[d.Length];
            Y[0] = d[0];

            for (int i = 2; i <= N; i++)
            {
                //Y[k]=d[k]-L[k]*Y[k-1];
                Y[i - 1] = d[i - 1] - (L[i - 2]) * (Y[i - 2]);

            }
            /****************  End of Ly=d   ****************************/


            /***************   Ux=Y   ********************************/
            //X[n]=Y[n]/U[n];
            R[N - 1] = Y[N - 1] / U[N - 1];
            //X[k]=(Y[k]-C[k]*X[k+1])/U[k];(n-1,,.....1)
            for (int i = N - 1; i >= 1; i--)
            {
                R[i - 1] = (Y[i - 1] - Ac[i - 1] * R[i]) / U[i - 1];
            }
            /***************   End of Ux=Y   *************************/
            for (int i = 0; i < R.Length; i++)
            {
                if (double.IsInfinity(R[i]) || double.IsNaN(R[i]))
                    return false;
            }
            return true;
        }
    }
}