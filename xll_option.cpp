﻿// xll_option.cpp - Black-Scholes/Merton option value and greeks.
#include "fms_option.h"
#include "xll/xll/xll.h"

#ifndef CATEGORY
#define CATEGORY "FRE6233"
#endif

using namespace xll;
using namespace fms::option;

// Create XML documentation and index.html in `$(TargetPath)` folder.
// Use `xsltproc file.xml -o file.html` to create HTML documentation.
#ifdef _DEBUG
xll_url_set FRE6233("https://keithalewis.github.io/FRE6233/");
Auto<Open> xao_template_docs([]() {

	return Documentation(CATEGORY, "Documentation for " CATEGORY ".");

});
#endif // _DEBUG

AddIn xai_option_moneyness(
	Function(XLL_DOUBLE, "xll_option_moneyness", "OPTION.MONEYNESS")
	.Arguments({
		Arg(XLL_HANDLEX, "v", "is a handle to a variate."),
		Arg(XLL_DOUBLE, "f", "is the forward."),
		Arg(XLL_DOUBLE, "sigma", "is the volatility."),
		Arg(XLL_DOUBLE, "k", "is the strike."),
		Arg(XLL_DOUBLE, "t", "is the time in years to expiration."),
		})
	.FunctionHelp("Return the option moneyness.")
	.Category(CATEGORY)
	.Documentation(R"(
Moneyness is \((\log(k/f) + \sigma^2 t/2)/\sigma\).
)")
);
double WINAPI xll_option_moneyness(HANDLEX v, double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	handle<base> v_(v);

	return moneyness(*v_, f, sigma*sqrt(t), fabs(k));
}

XLL_CONST(WORD, OPTION_PUT, contract::PUT, "European put option", CATEGORY, "");
XLL_CONST(WORD, OPTION_CALL, contract::CALL, "European call option", CATEGORY, "");
XLL_CONST(WORD, OPTION_DIGITAL_PUT, contract::DIGITAL_PUT, "European digital put option", CATEGORY, "");
XLL_CONST(WORD, OPTION_DIGITAL_CALL, contract::DIGITAL_CALL, "European digital call option", CATEGORY, "");

AddIn xai_option_value(
	Function(XLL_DOUBLE, "xll_option_value", "OPTION.VALUE")
	.Arguments({
		Arg(XLL_HANDLEX, "v", "is a handle to a variate."),
		Arg(XLL_DOUBLE, "S", "is the spot."),
		Arg(XLL_DOUBLE, "sigma", "is the volatility."),
		Arg(XLL_WORD, "option", "is the contract type from OPTION_*."),
		Arg(XLL_DOUBLE, "k", "is the strike."),
		Arg(XLL_DOUBLE, "t", "is the time in years to expiration."),
		Arg(XLL_DOUBLE, "r", "is the continuously compouned interest rate. Default is 0."),
		})
	.FunctionHelp("Return the option value.")
	.Category(CATEGORY)
	.Documentation(R"(
Option value is 
\(e^{-rt}E[\phi(se^{rt + \sigma B_t - \sigma^2t/2})]\)
where \(\phi\) is the option payoff.
Note if \(r = 0\) this gives the Black value where
\(S\) is the forward.
)")
);
double WINAPI xll_option_value(HANDLEX v, double S, double sigma, contract flag, double k, double t, double r)
{
#pragma XLLEXPORT
	handle<base> v_(v);

	return bsm::value(*v_, r, S, sigma, flag, k, t);
}

AddIn xai_option_delta(
	Function(XLL_DOUBLE, "xll_option_delta", "OPTION.DELTA")
	.Arguments({
		Arg(XLL_HANDLEX, "v", "is a handle to a variate."),
		Arg(XLL_DOUBLE, "S", "is the spot."),
		Arg(XLL_DOUBLE, "sigma", "is the volatility."),
		Arg(XLL_WORD, "option", "is the contract type from OPTION_*."),
		Arg(XLL_DOUBLE, "k", "is the strike."),
		Arg(XLL_DOUBLE, "t", "is the time in years to expiration."),
		Arg(XLL_DOUBLE, "r", "is the continuously compouned interest rate. Default is 0."),
		})
	.FunctionHelp("Return the option call or put delta.")
	.Category(CATEGORY)
	.Documentation(R"(
Option delta is the derivative of option value with respect to forward.
)")
);
double WINAPI xll_option_delta(HANDLEX v, double S, double sigma, contract flag, double k, double t, double r)
{
#pragma XLLEXPORT
	handle<base> v_(v);

	return bsm::delta(*v_, r, S, sigma, flag, k, t);
}

AddIn xai_option_gamma(
	Function(XLL_DOUBLE, "xll_option_gamma", "OPTION.GAMMA")
	.Arguments({
		Arg(XLL_HANDLEX, "v", "is a handle to a variate."),
		Arg(XLL_DOUBLE, "S", "is the spot."),
		Arg(XLL_DOUBLE, "sigma", "is the volatility."),
		Arg(XLL_WORD, "option", "is the contract type from OPTION_*."),
		Arg(XLL_DOUBLE, "k", "is the strike."),
		Arg(XLL_DOUBLE, "t", "is the time in years to expiration."),
		Arg(XLL_DOUBLE, "r", "is the continuously compouned interest rate. Default is 0."),
		})
		.FunctionHelp("Return the option call (k > 0) or put (k < 0) gamma.")
	.Category(CATEGORY)
	.Documentation(R"(
Option gamma is the second derivative of option value with respect to forward.
)")
);
double WINAPI xll_option_gamma(HANDLEX v, double S, double sigma, contract flag, double k, double t, double r)
{
#pragma XLLEXPORT
	handle<base> v_(v);

	return bsm::gamma(*v_, r, S, sigma, flag, k, t);
}

AddIn xai_option_vega(
	Function(XLL_DOUBLE, "xll_option_vega", "OPTION.VEGA")
	.Arguments({
		Arg(XLL_HANDLEX, "v", "is a handle to a variate."),
		Arg(XLL_DOUBLE, "S", "is the spot."),
		Arg(XLL_DOUBLE, "sigma", "is the volatility."),
		Arg(XLL_WORD, "option", "is the contract type from OPTION_*."),
		Arg(XLL_DOUBLE, "k", "is the strike."),
		Arg(XLL_DOUBLE, "t", "is the time in years to expiration."),
		Arg(XLL_DOUBLE, "r", "is the continuously compouned interest rate. Default is 0."),
		})
		.FunctionHelp("Return the option call (k > 0) or put (k < 0) vega.")
	.Category(CATEGORY)
	.Documentation(R"(
Option vega is the derivative of option value with respect to vol.
)")
);
double WINAPI xll_option_vega(HANDLEX v, double S, double sigma, contract flag, double k, double t, double r)
{
#pragma XLLEXPORT
	handle<base> v_(v);

	return bsm::vega(*v_, r, S, sigma, flag, k, t);
}

AddIn xai_option_theta(
	Function(XLL_DOUBLE, "xll_option_theta", "OPTION.THETA")
	.Arguments({
		Arg(XLL_HANDLEX, "v", "is a handle to a variate."),
		Arg(XLL_DOUBLE, "f", "is the forward."),
		Arg(XLL_DOUBLE, "sigma", "is the volatility."),
		Arg(XLL_DOUBLE, "k", "is the strike."),
		Arg(XLL_DOUBLE, "t", "is the time in years to expiration"),
		Arg(XLL_DOUBLE, "_dt", "is an optional time increment. Default is 1/250."),
		})
		.FunctionHelp("Return the option call (k > 0) or put (k < 0) theta.")
	.Category(CATEGORY)
	.Documentation(R"(
Option theta is the derivative of option value with respect to time.
)")
);
double WINAPI xll_option_theta(HANDLEX v, double f, double sigma, double k, double t, double dt)
{
#pragma XLLEXPORT
	if (dt == 0) {
		dt = 1. / 250;
	}
	handle<base> v_(v);

	return black::theta(*v_, f, sigma, k, t, dt);
}

AddIn xai_option_implied(
	Function(XLL_DOUBLE, "xll_option_implied", "OPTION.IMPLIED")
	.Arguments({
		Arg(XLL_HANDLEX, "v", "is a handle to a variate."),
		Arg(XLL_DOUBLE, "f", "is the forward."),
		Arg(XLL_DOUBLE, "v", "is the option value."),
		Arg(XLL_DOUBLE, "k", "is the strike."),
		Arg(XLL_DOUBLE, "t", "is the time in years to expiration."),
		Arg(XLL_DOUBLE, "_sigma", "is an optional initial guess. Default is 0.1."),
		Arg(XLL_WORD, "_n", "is an optional maximum number of iterations. Default is 100."),
		Arg(XLL_DOUBLE, "_tol", "is an optional absolute tolerance. Default is square root of machine epsilon."),
		})
	.FunctionHelp("Return the option call (k > 0) or put (k < 0) implied vol.")
	.Category(CATEGORY)
	.Documentation(R"(
Option implied volatility is the inverse of value.
)")
);
double WINAPI xll_option_implied(HANDLEX v, double f, double v0, double k, double t, double sigma, unsigned n, double tol)
{
#pragma XLLEXPORT
	handle<base> v_(v);

	return black::implied(*v_, f, v0, k, sigma * sqrt(t), n, tol);
}
